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
 * @file            ComWin.cpp
 *
 * communication functions for UMB ctrl library (windows)
 *
 * Please note, that this is a demo file. So for the purpose of
 * better readability and understanding we omitted most of the security queries.
 * If you like to adopt parts of these sources into your own software,
 * please make sure, that you enhance them with all the security queries,
 * which seem appropriate to you or which are demanded by your coding guidelines.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "SerialPort.h"
#include "ComWin.h"

typedef struct
{
    COM_CONFIG_T config;
    CSerialPort port;
} COM_HANDLE_T;

static Std_ReturnType ComInit(void* pUserHandle);
static Std_ReturnType ComDeinit(void* pUserHandle);
static Std_ReturnType ComUse(void* pUserHandle);
static Std_ReturnType ComUnuse(void* pUserHandle);
static Std_ReturnType ComTx(void* pUserHandle, const uint32 length, const uint8 * const bytes);
static Std_ReturnType ComRxAvail(void* pUserHandle, uint32 * const pAvail);
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
            memset(&pComHandle->port, 0, sizeof(pComHandle->port));
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

    try
    {
        int number = std::strtoul(pComHandle->config.serialIf, NULL, 10);
        pComHandle->port.Open(number, pComHandle->config.baudrate, CSerialPort::NoParity, 8, CSerialPort::OneStopBit, CSerialPort::NoFlowControl);
    }
    catch (CSerialException& e)
    {
        printf("Unexpected CSerialPort exception, Error:%u\n", e.m_dwError);
        //UNREFERENCED_PARAMETER(e);
        return E_NOT_OK;
    }

    return E_OK;
}

static Std_ReturnType ComDeinit(void* pUserHandle)
{
    COM_HANDLE_T* pComHandle = (COM_HANDLE_T*)pUserHandle;

    pComHandle->port.Close();

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

    pComHandle->port.Write(bytes, length);

    return E_OK;
}

static Std_ReturnType ComRxAvail(void* pUserHandle, uint32* const pAvail)
{
    COM_HANDLE_T* pComHandle = (COM_HANDLE_T*)pUserHandle;

    *pAvail = pComHandle->port.BytesWaiting();

    return E_OK;
}

static Std_ReturnType ComRx(void* pUserHandle, const sint32 timeoutMs, const uint32 maxLen, uint32* const pLength, uint8* const pBytes)
{
    COM_HANDLE_T* pComHandle = (COM_HANDLE_T*)pUserHandle;
    COMMTIMEOUTS timeouts;

    pComHandle->port.GetTimeouts(timeouts);
    timeouts.ReadIntervalTimeout = MAXDWORD;
    timeouts.ReadTotalTimeoutMultiplier = MAXDWORD;
    timeouts.ReadTotalTimeoutConstant = timeoutMs;
    pComHandle->port.SetTimeouts(timeouts);

    *pLength = pComHandle->port.Read(pBytes, maxLen);

    return E_OK;
}

static Std_ReturnType ComRxClearBuf(void* pUserHandle)
{
    COM_HANDLE_T* pComHandle = (COM_HANDLE_T*)pUserHandle; 
    
    pComHandle->port.ClearReadBuffer();

    return E_OK;
}

