////////////////////////////////////////////////////////////////////////////////
//     _____      _            __  __ _       _____           _     _    _    //
//    / ____|    | |          / _|/ _| |     / ____|         | |   | |  | |   //
//   | |  __     | |    _   _| |_| |_| |_   | |  __ _ __ ___ | |__ | |__| |   //
//   | | |_ |    | |   | | | |  _|  _| __|  | | |_ | '_ ` _ \| '_ \|  __  |   //
//   | |__| |_   | |___| |_| | | | | | |_   | |__| | | | | | | |_) | |  | |   //
//    \_____(_)  |______\__,_|_| |_|  \__|   \_____|_| |_| |_|_.__/|_|  |_|   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/***************************************************************************//**
 * @file            ComLinux.cpp
 *
 * communication functions for UMB ctrl library (linux)
 * 
 * Please note, that this is a demo file. So for the purpose of
 * better readability and understanding we omitted most of the security queries.
 * If you like to adopt parts of these sources into your own software,
 * please make sure, that you enhance them with all the security queries,
 * which seem appropriate to you or which are demanded by your coding guidelines.
 *
 ******************************************************************************/
#include "ComLinux.h"

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>
#include <fcntl.h>
#include <linux/serial.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>

typedef struct
{
    COM_CONFIG_T config;
    int m_fdTTY;
} COM_HANDLE_T;

static Std_ReturnType ComInit(void* pUserHandle);
static Std_ReturnType ComDeinit(void* pUserHandle);
static Std_ReturnType ComUse(void* pUserHandle);
static Std_ReturnType ComUnuse(void* pUserHandle);
static Std_ReturnType ComTx(void* pUserHandle, const uint32 length, const uint8* const bytes);
static Std_ReturnType ComRxAvail(void* pUserHandle, uint32* const pAvail);
static Std_ReturnType ComRx(void* pUserHandle, const sint32 timeoutMs, const uint32 maxLen, uint32* const pLength, uint8* const pBytes);
static Std_ReturnType ComRxClearBuf(void* pUserHandle);

UMB_CTRL_COM_FUNCTION_T* ComFunctionInit(COM_CONFIG_T* pConfig)
{
    UMB_CTRL_COM_FUNCTION_T* pComFunction = (UMB_CTRL_COM_FUNCTION_T*)malloc(sizeof(UMB_CTRL_COM_FUNCTION_T));

    if (pComFunction)
    {
        pComFunction->pUserHandle = malloc(sizeof(COM_HANDLE_T));

        if (pComFunction->pUserHandle)
        {
            COM_HANDLE_T* pComHandle = (COM_HANDLE_T*)pComFunction->pUserHandle;

            pComHandle->config = *pConfig;
            pComHandle->m_fdTTY = -1;
        }

        pComFunction->pfnInit = ComInit;
        pComFunction->pfnDeinit = ComDeinit;
        pComFunction->pfnUse = ComUse;
        pComFunction->pfnUnuse = ComUnuse;

        pComFunction->pfnTx = ComTx;
        pComFunction->pfnRxAvail = ComRxAvail;
        pComFunction->pfnRx = ComRx;
        pComFunction->pfnRxClearBuf = ComRxClearBuf;
    }

    return pComFunction;
}

bool ComFunctionDeinit(UMB_CTRL_COM_FUNCTION_T* pComFunction)
{
    free(pComFunction->pUserHandle);
    free(pComFunction);

    return true;
}

static Std_ReturnType ComInit(void* pUserHandle)
{
    COM_HANDLE_T* pComHandle = (COM_HANDLE_T*)pUserHandle;

    pComHandle->m_fdTTY = open(pComHandle->config.serialIf, O_RDWR | O_NOCTTY | O_SYNC); 	// must be blocking!
    if (pComHandle->m_fdTTY >= 0)
    {
    	struct termios tio;
        speed_t speed;
		bzero(&tio, sizeof(tio)); /* clear struct for new port settings */

		/* port configuration */
        switch (pComHandle->config.baudrate)
        {
            case 9600:  speed = B9600; break;

            case 19200:
            default:    speed = B19200; break;
        }
		cfsetospeed(&tio, speed);					// configured baud rate
		tio.c_cflag &= ~(PARENB | CSIZE);   		// parity disabled
		tio.c_cflag |= CS8;                 		// 8 data bits
		tio.c_cflag &= ~CSTOPB;             		// one stop bit

		tio.c_cflag |= (CLOCAL | CREAD);            // ignore modem control lines
		tio.c_cflag &= ~CRTSCTS;                    // disable hardware flow control
		tio.c_iflag &= ~(IXON | IXOFF | IXANY);     // disable XON XOFF (for transmit and receive)
		tio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // raw input
		tio.c_oflag &= ~OPOST;                      // raw output
		cfsetispeed(&tio, B0);                      // input speed equals output speed

		if(tcsetattr(pComHandle->m_fdTTY, TCSANOW, &tio) < 0)
		{
			return false;
		}

		// clear i/o buffer
		tcflush(pComHandle->m_fdTTY, TCIOFLUSH);

		return E_OK;
    }
    else
    {
        printf("Opening TTY %s failed! (%d - %s)\n", pComHandle->config.serialIf, errno, strerror(errno));
        return E_NOT_OK;
    }

    return E_OK;
}

static Std_ReturnType ComDeinit(void* pUserHandle)
{
    COM_HANDLE_T* pComHandle = (COM_HANDLE_T*)pUserHandle;

    if (pComHandle->m_fdTTY != -1)
    {
        close(pComHandle->m_fdTTY);
    }

    return E_OK;
}

static Std_ReturnType ComUse(void* pUserHandle)
{
    return E_OK;
}

static Std_ReturnType ComUnuse(void* pUserHandle)
{
    return E_OK;
}

static Std_ReturnType ComTx(void* pUserHandle, const uint32 length, const uint8* const bytes)
{
    COM_HANDLE_T* pComHandle = (COM_HANDLE_T*)pUserHandle;

    if (write(pComHandle->m_fdTTY, bytes, length) > 0)
    {
        return E_OK;
    }

    return E_NOT_OK;
}

static Std_ReturnType ComRxAvail(void* pUserHandle, uint32* const pAvail)
{
    COM_HANDLE_T* pComHandle = (COM_HANDLE_T*)pUserHandle;

    int bytesAvail;
    ioctl(pComHandle->m_fdTTY, FIONREAD, &bytesAvail);
    *pAvail = (uint32)bytesAvail;

    return E_OK;
}

static Std_ReturnType ComRx(void* pUserHandle, const sint32 timeoutMs, const uint32 maxLen, uint32* const pLength, uint8* const pBytes)
{
    COM_HANDLE_T* pComHandle = (COM_HANDLE_T*)pUserHandle;
    int retval;
	fd_set set;
	struct timeval timeout;

	if((pComHandle->m_fdTTY < 0) || (pLength == nullptr) || (pBytes == nullptr))
	{
		return E_NOT_OK;
	}

	FD_ZERO(&set);
	FD_SET(pComHandle->m_fdTTY, &set);

	timeout.tv_sec = timeoutMs / 1000;
	timeout.tv_usec = (timeoutMs % 1000) * 1000;

	retval = select(pComHandle->m_fdTTY + 1, &set, NULL, NULL, &timeout);
	if(retval > 0)
	{
		retval = read(pComHandle->m_fdTTY, pBytes, maxLen);
		if(retval > 0)
		{
			*pLength = retval;
			return E_OK;
		}
	}

	return E_NOT_OK;
}

static Std_ReturnType ComRxClearBuf(void* pUserHandle)
{
    COM_HANDLE_T* pComHandle = (COM_HANDLE_T*)pUserHandle;
    tcflush(pComHandle->m_fdTTY, TCIFLUSH);

    return E_OK;
}
