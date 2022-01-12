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
 * @file            UmbCtrlTest.cpp
 *
 * test program to demonstrate the use of the UMB library
 *
 * Please note, that this is a demo file. So for the purpose of
 * better readability and understanding we omitted most of the security queries.
 * If you like to adopt parts of these sources into your own software,
 * please make sure, that you enhance them with all the security queries,
 * which seem appropriate to you or which are demanded by your coding guidelines.
 *
 ******************************************************************************/

#if _MSC_VER
#include <stdafx.h>
#include "pthread.h"
#include "ComWin.h"
#elif __linux__
// TODO: Define _USE_NCURSES to enable character graphics for firmware update functions
//#define _USE_NCURSES
#ifdef _USE_NCURSES
#include <ncurses.h>
#endif
#include <unistd.h>
#include <pthread.h>
#include "ComLinux.h"
#endif

#include <string>
#include <malloc.h>

#include "UmbControllerLib.h"

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

typedef struct
{
    UMB_CTRL_T *pUmbCtrl;
    UMB_ADDRESS_T address;
    uint8* fileName;
    bool reboot;
    UMB_CTRL_STATUS_T threadReturn;
} FW_UPDATE_T;

static void writeMemory(UMB_CTRL_T* pUmbCtrl, UMB_ADDRESS_T umbAddress);
static void getChannelInfo(UMB_CTRL_T* pUmbCtrl, UMB_ADDRESS_T umbAddress);
static void getChannelData(UMB_CTRL_T* pUmbCtrl, UMB_ADDRESS_T umbAddress);
static void firmwareUpdate(UMB_CTRL_T* pUmbCtrl, UMB_ADDRESS_T umbAddress);
static void printFileInfo(const uint8 fileName[], UMB_CTRL_FW_FILE_T* fileInfo);
static void doUpdateAnimation(pthread_t updateThread);
static void spinBeachBall(char* beachBall);
static void* firmwareUpdate_thread(void* arg);

int main(int argc, char* argv[])
{
    UMB_CTRL_STATUS_T status;
    UMB_CTRL_T *pUmbCtrl;

    // UMB lib version
    UMB_CTRL_VERSION_T version = UmbCtrl_GetVersion();
    printf("UMB Lib Version: major=%d, minor=%d\n", version.major, version.minor);

    // Initialization
    // TODO: Adjust to used serial interface
#if __linux__
    // Use full filename
    char serialIf[] = "/dev/ttyS0";
#else
    // Use only port number
    char serialIf[] = "1";
#endif

    COM_CONFIG_T comConfig;
    UMB_CTRL_COM_FUNCTION_T * pUmbCtrlComFunction;

    // TODO: Adjust to used baudrate
    comConfig.baudrate = 19200;
    comConfig.serialIf = serialIf;
    pUmbCtrlComFunction = ComFunctionInit(&comConfig);

    pUmbCtrl = malloc(UmbCtrl_GetHandleSize());
    status = UmbCtrl_Init(pUmbCtrl, pUmbCtrlComFunction, 0);

    // Further processing
    UMB_ADDRESS_T umbAddress;
    // TODO: Adjust to used class id / device id
    umbAddress.deviceId = 0x01; // device id: 1
    umbAddress.classId = 0x70;  // class id: 7 = weather station

    str8 name[41] = { 0 };
    status = UmbCtrl_GetDevName(pUmbCtrl, umbAddress, name);
    if (status.global == UMB_CTRL_STATUS_OK)
    {
        printf("Device name: %s\n", name);
    }
    else
    {
        printf("ERROR [request device name]: lib=0x%0X dev=0x%0X\n", 
            status.detail.library, status.detail.device);
    }

    ERROR_STATUS_T deviceStatus;
    status = UmbCtrl_GetDevStatus(pUmbCtrl, umbAddress, &deviceStatus);
    if (status.global == UMB_CTRL_STATUS_OK)
    {
        printf("Device status: %d\n", deviceStatus);
    }
    else
    {
        printf("ERROR [request device status]: lib=0x%0X dev=0x%0X\n",
            status.detail.library, status.detail.device);
    }

    //writeMemory(pUmbCtrl, umbAddress);
    //getChannelInfo(pUmbCtrl, umbAddress);
    //getChannelData(pUmbCtrl, umbAddress);
    firmwareUpdate(pUmbCtrl, umbAddress);

    // deinitialization
    UmbCtrl_Deinit(pUmbCtrl);
    free(pUmbCtrl);
    ComFunctionDeinit(pUmbCtrlComFunction);
}

static void writeMemory(UMB_CTRL_T* pUmbCtrl, UMB_ADDRESS_T umbAddress)
{
    uint8 description[41] = { "My new device description" };

    UmbCtrl_WriteMem(pUmbCtrl, umbAddress, 76, 40, description);
    UmbCtrl_ReadMem(pUmbCtrl, umbAddress, 76, 40, description);
    printf("New device description: %s\n", description);

    // reset the device and wait for it to reboot
    UmbCtrl_Reset(pUmbCtrl, umbAddress, 0);
#if _MSC_VER
    Sleep(4000);
#elif __linux
    usleep(4000000);
#endif

    UmbCtrl_ReadMem(pUmbCtrl, umbAddress, 76, 40, description);
    printf("New device description after reboot: %s\n", description);
}

static void getChannelInfo(UMB_CTRL_T* pUmbCtrl, UMB_ADDRESS_T umbAddress)
{
    UMB_CTRL_STATUS_T status;
    uint16 numChannels;
    uint8 numBlocks;
    uint16 channel[128];
    UMB_CTRL_CHANNELINFO_T channelInfo;

    status = UmbCtrl_GetNumChannels(pUmbCtrl, umbAddress, &numChannels, &numBlocks);
    printf("Channels = %d\tBlocks = %d\n", numChannels, numBlocks);

    for (uint8 j = 0; j < numBlocks; j++)
    {
        status = UmbCtrl_GetChannels(pUmbCtrl, umbAddress, j, (uint8*)&numChannels, channel);

        for (uint8 i = 0; i < numChannels; i++)
        {
            printf("Block[%d] Channel[%d] = %d\n", j, i, channel[i]);

            status = UmbCtrl_GetChannelInfo(pUmbCtrl, umbAddress, channel[i], &channelInfo);
            printf("\tNumber = %d\n", channelInfo.channel);
            printf("\tName = %s\n", channelInfo.name);
            printf("\tUnit = %s\n", channelInfo.unitName);
            printf("\tValue type = %d, Data type = %d\n", channelInfo.valType, channelInfo.dataType);
            switch (channelInfo.dataType)
            {
                case DATA_TYPE_F64: printf("\tMin = %.2lf, Max = %.2lf\n", channelInfo.min.f64_val, channelInfo.max.f64_val); break;
                case DATA_TYPE_F32: printf("\tMin = %.2f, Max = %.2f\n", channelInfo.min.f32_val, channelInfo.max.f32_val); break;
                case DATA_TYPE_S32: printf("\tMin = %d, Max = %d\n", channelInfo.min.s32_val, channelInfo.max.s32_val); break;
                case DATA_TYPE_U32: printf("\tMin = %d, Max = %d\n", channelInfo.min.u32_val, channelInfo.max.u32_val); break;
                case DATA_TYPE_S16: printf("\tMin = %d, Max = %d\n", channelInfo.min.s16_val, channelInfo.max.s16_val); break;
                case DATA_TYPE_U16: printf("\tMin = %d, Max = %d\n", channelInfo.min.u16_val, channelInfo.max.u16_val); break;
                case DATA_TYPE_S8:  printf("\tMin = %d, Max = %d\n", channelInfo.min.s8_val, channelInfo.max.s8_val);  break;
                case DATA_TYPE_U8:  printf("\tMin = %d, Max = %d\n", channelInfo.min.u8_val, channelInfo.max.u8_val);  break;
                default: break;
            }
        }
    }
}

static void getChannelData(UMB_CTRL_T* pUmbCtrl, UMB_ADDRESS_T umbAddress)
{
    UMB_CTRL_STATUS_T status;
    uint8 numChannels = 3;
    uint16 channel[3] = { 100, 600, 900 };
    MEAS_CHANNEL_VALUE_T channelValue[3];

    // data query once a second, 10 times
    for (uint8 j = 0; j < 10; j++)
    {
        status = UmbCtrl_GetMultiChannelData(pUmbCtrl, umbAddress, numChannels, channel, channelValue);

        for (uint8 i = 0; i < numChannels; i++)
        {
            if (channelValue[i].ch_status == ERROR_STATUS_OK)
            {
                switch (channelValue[i].ch_data_type)
                {
                    case DATA_TYPE_F64: printf("Channel: %u\tValue:%lf \n", channelValue[i].ch_number, channelValue[i].ch_value.f64_val); break;
                    case DATA_TYPE_F32: printf("Channel: %u\tValue:%f  \n", channelValue[i].ch_number, channelValue[i].ch_value.f32_val); break;
                    case DATA_TYPE_S32: printf("Channel: %u\tValue:%d,\n", channelValue[i].ch_number, channelValue[i].ch_value.s32_val); break;
                    case DATA_TYPE_U32: printf("Channel: %u\tValue:%d,\n", channelValue[i].ch_number, channelValue[i].ch_value.u32_val); break;
                    case DATA_TYPE_S16: printf("Channel: %u\tValue:%d, \n", channelValue[i].ch_number, channelValue[i].ch_value.s16_val); break;
                    case DATA_TYPE_U16: printf("Channel: %u\tValue:%d, \n", channelValue[i].ch_number, channelValue[i].ch_value.u16_val); break;
                    case DATA_TYPE_S8:  printf("Channel: %u\tValue:%d, \n", channelValue[i].ch_number, channelValue[i].ch_value.s8_val);  break;
                    case DATA_TYPE_U8:  printf("Channel: %u\tValue:%d, \n", channelValue[i].ch_number, channelValue[i].ch_value.u8_val);  break;
                    default: break;
                }
            }
            else
            {
                printf("Channel: %u\tStatus: %u\n", channelValue[i].ch_number, (uint8)channelValue[i].ch_status);
            }
        }

    #if _MSC_VER
        Sleep(1000);
    #elif __linux
        usleep(1000000);
    #endif
    }
}

static volatile bool updateRunning = false;
static volatile uint8 updateProgress = 0;

static void firmwareUpdate(UMB_CTRL_T* pUmbCtrl, UMB_ADDRESS_T umbAddress)
{
    pthread_t updateThread;
    FW_UPDATE_T fwUpdate;
    // TODO: Adjust path and name of the used firmware file (only .bin format is supported)
    uint8 fileName[] = { "C:\\Projekte\\UmbController\\MARWIS_Release_V46_RC1.bin" };
    fwUpdate.pUmbCtrl = pUmbCtrl;
    fwUpdate.address = umbAddress;
    fwUpdate.fileName = fileName;
    fwUpdate.reboot = true;

    UMB_CTRL_FW_FILE_T fileInfo;
    UmbCtrl_GetFwFileInfo(fileName, &fileInfo);
    printFileInfo(fileName, &fileInfo);
    printf("Press ENTER to continue!\n");
    char c = getchar();
    if ((c == '\n') || (c == '\r'))
    {
        updateRunning = true;
        pthread_create(&updateThread, NULL, firmwareUpdate_thread, &fwUpdate);
        doUpdateAnimation(updateThread);

        printf("\n\n");
        UMB_CTRL_STATUS_T* pStatus = &fwUpdate.threadReturn;
        if (pStatus->global != UMB_CTRL_STATUS_OK)
        {
            switch (pStatus->detail.library)
            {
            case UMB_CTRL_LIB_STATUS_TIMEOUT:
                printf("Timeout ERROR\n");
                break;
            case UMB_CTRL_LIB_STATUS_PARSER:
                printf("Parser ERROR\n");
                break;
            case UMB_CTRL_LIB_STATUS_OK:
            default:
                printf("Error: 0x%04x\n", pStatus->global);
                break;
            }
        }
        else
        {
            printf("Update finished!\n");
        }
    }
}

static void printFileInfo(const uint8 fileName[], UMB_CTRL_FW_FILE_T* fileInfo)
{
    printf("%s\n", fileName);
    printf("Project:\t%u\n", fileInfo->project);
    printf("Version:\t%hhu.%hhu\n", (uint8)(fileInfo->version / 10), (uint8)(fileInfo->version % 10));
}

#if _MSC_VER
static void doUpdateAnimation(pthread_t updateThread)
{
    char beachBall = '-';
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(output, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(output, &cursorInfo);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(output, &csbi);
    COORD coord = { 0, csbi.dwCursorPosition.Y };

    while (updateRunning)
    {
        SetConsoleCursorPosition(output, coord);
        printf("FW-Update: |");
        for (int i = 0; i < 50; i++)
        {
            char c = (updateProgress / 2) <= i ? ' ' : '*';
            printf("%c", c);
        }

        printf("| %c %3hhu%%", beachBall, updateProgress);
        spinBeachBall(&beachBall);
        Sleep(75);
    }

    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(output, &cursorInfo);
}
#elif __linux
#ifdef _USE_NCURSES
static void doUpdateAnimation(pthread_t updateThread)
{
    char beachBall = '-';
    int x, y;

    filter();
    SCREEN* s = newterm(NULL, stdout, stdin);
    if (s == NULL)
        return;

    curs_set(0);
    noecho();
    getyx(stdscr, y, x);

    while (updateRunning)
    {
        mvprintw(y, 0, "FW-Update: |");
        for (int i = 0; i < 50; i++)
        {
            char c = (updateProgress / 2) <= i ? ' ' : '*';
            printw("%c", c);
        }

        printw("| %c %3hhu%%", beachBall, updateProgress);
        spinBeachBall(&beachBall);
        refresh();

        usleep(100000);
    }

    curs_set(1);
    endwin();
}
#else // USE_NCURSES undefined
static void doUpdateAnimation(pthread_t updateThread)
{
    uint8 cnt = 0;
    
    while (updateRunning)
    {
        if (updateProgress / 2)
        {
            printf("*");
            fflush(stdout);
            cnt ++;
            if (cnt > 50)
            {
                printf("\n");
                cnt = 0;
            }
        }
        usleep(1000000);
    }
}
#endif
#endif

static void spinBeachBall(char* beachBall)
{
    switch (*beachBall)
    {
    case '-':
        *beachBall = '\\';
        break;
    case '\\':
        *beachBall = '|';
        break;
    case '|':
        *beachBall = '/';
        break;
    case '/':
        *beachBall = '-';
        break;
    default:
        *beachBall = '-';
        break;
    }
}

static void* firmwareUpdate_thread(void* arg)
{
    FW_UPDATE_T* fw_arg = (FW_UPDATE_T*)arg;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    // UmbCtrl_UpdateFirmware() returns as soon as the update is completed.
    // Depending on file size and baudrate this can last up to 1 - 2 min!
    fw_arg->threadReturn = UmbCtrl_UpdateFirmware(fw_arg->pUmbCtrl, fw_arg->address, fw_arg->fileName, fw_arg->reboot, &updateProgress);
    updateRunning = false;

    pthread_exit(NULL);
    return NULL;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
