////////////////////////////////////////////////////////////////////////////////
//     _____      _            __  __ _       _____           _     _    _    //
//    / ____|    | |          / _|/ _| |     / ____|         | |   | |  | |   //
//   | |  __     | |    _   _| |_| |_| |_   | |  __ _ __ ___ | |__ | |__| |   //
//   | | |_ |    | |   | | | |  _|  _| __|  | | |_ | '_ ` _ \| '_ \|  __  |   //
//   | |__| |_   | |___| |_| | | | | | |_   | |__| | | | | | | |_) | |  | |   //
//    \_____(_)  |______\__,_|_| |_|  \__|   \_____|_| |_| |_|_.__/|_|  |_|   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
// @copyright G.Lufft Mess- und Regeltechnik GmbH CONFIDENTIAL
//
// Unpublished Copyright (c) 2014-2018 "G.Lufft Mess- und Regeltechnik GmbH", All Rights Reserved.
// NOTICE: All information contained herein is, and remains the property of "G.Lufft Mess- und Regeltechnik GmbH".
// The intellectual and technical concepts contained herein are proprietary to "G.Lufft Mess- und Regeltechnik GmbH"
// and may be covered by U.S. and Foreign Patents, patents in process, and are protected by trade secret or copyright
// law. Dissemination of this information or reproduction of this material is strictly forbidden unless prior
// written permission is obtained from "G.Lufft Mess- und Regeltechnik GmbH". Access to the source code contained
// herein is hereby forbidden to anyone except current "G.Lufft Mess- und Regeltechnik GmbH" employees, managers
// or contractors who have executed Confidentiality and Non-disclosure agreements explicitly covering such access.
//
// The copyright notice above does not evidence any actual or intended publication or disclosure of this source
// code, which includes information that is confidential and/or proprietary, and is a trade secret, of "G.Lufft Mess-
// und Regeltechnik GmbH". ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY
// OF OR THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF "G.Lufft Mess- und Regeltechnik
// GmbH" IS STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
// POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS TO REPRODUCE,
// DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING THAT IT MAY DESCRIBE, IN WHOLE
// OR IN PART.
//
////////////////////////////////////////////////////////////////////////////////

/***************************************************************************//**
 * @file            UmbControllerLib.h
 * @copyright       G. Lufft, Mess- und Regeltechnik GmbH, Fellbach, Germany
 ******************************************************************************/

#ifndef UMB_CONTROLLER_LIB_H
#define UMB_CONTROLLER_LIB_H

 ////////////////////////////////////////////////////////////////////////////////
 //                                 includes                                   //
 ////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "Umb_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
//                    type, macro and constant definitions                    //
////////////////////////////////////////////////////////////////////////////////


#if WIN32 && defined DLL_EXPORT
#define DECL_DLL __declspec(dllexport)
#else
#define DECL_DLL
#endif

#define UMB_CTRL_STATUS_OK 0x0000

//! type of the UMB ctrl lib handle
typedef void UMB_CTRL_T;

//! version of the UMB ctrl library
typedef struct
{
	uint16 major;
	uint16 minor;
} UMB_CTRL_VERSION_T;

//!< status of the UMB ctrl library
PACKED_STRUCT
typedef enum
{
	UMB_CTRL_LIB_STATUS_OK				= 0x00,
	UMB_CTRL_LIB_STATUS_INIT_ERROR		= 0x01,
	UMB_CTRL_LIB_STATUS_INVALID_PARAM	= 0x02,
	UMB_CTRL_LIB_STATUS_TIMEOUT			= 0x03,
	UMB_CTRL_LIB_STATUS_CRC				= 0x04,
	UMB_CTRL_LIB_STATUS_SUBCMD			= 0x05,
	UMB_CTRL_LIB_STATUS_PARSER			= 0x06,
	UMB_CTRL_LIB_STATUS_FW_UPDATE		= 0x07,
	UMB_CTRL_LIB_STATUS_UNKNOWN_ERR		= 0xFF
} UMB_CTRL_LIB_STATUS_T;
PACKED_STRUCT_END

//! status of the UMB module (library + device)
typedef union
{
	uint16 global;	//!< global status
PACKED_STRUCT
	struct
	{
		UMB_CTRL_LIB_STATUS_T	library;	//status of the library
		ERROR_STATUS_T			device;		//!< UMB status of the device
	} detail;
PACKED_STRUCT_END
} UMB_CTRL_STATUS_T;

//! callback functions for communication
typedef struct
{
	void* pUserHandle;

	Std_ReturnType(*pfnInit)	(void* pUserHandle);
	Std_ReturnType(*pfnDeinit)	(void* pUserHandle);
	Std_ReturnType(*pfnUse)		(void* pUserHandle);
	Std_ReturnType(*pfnUnuse)	(void* pUserHandle);

	Std_ReturnType(*pfnTx)		(void* pUserHandle, const uint32 length, const uint8* const pBytes);

	Std_ReturnType(*pfnRxAvail)	(void* pUserHandle, uint32* const pAvail);
	Std_ReturnType(*pfnRx)		(void* pUserHandle, const sint32 timeoutMs, const uint32 maxLen, uint32* const pLength, uint8* const pBytes);
	Std_ReturnType(*pfnRxClearBuf)(void* pUserHandle);

} UMB_CTRL_COM_FUNCTION_T;

//! channel info
typedef struct
{
	uint16 channel;
	str8 name[20+1];
	str8 unitName[15+1];
	MEAS_VALUE_TYPE_T valType;
	MEAS_DATA_TYPE_T dataType;
	MEAS_VAL_T min;
	MEAS_VAL_T max;
} UMB_CTRL_CHANNELINFO_T;

//! info about the firmware update file
typedef struct
{
	uint32 project;	//!< project number
	uint32 version;	//!< firmware version
} UMB_CTRL_FW_FILE_T;


////////////////////////////////////////////////////////////////////////////////
//                       external function declarations                       //
////////////////////////////////////////////////////////////////////////////////

/***************************************************************************//**
 * Get the version of the UMB controller library
 *
 * @param[in]       void
 * @return          version
 ******************************************************************************/
DECL_DLL UMB_CTRL_VERSION_T UmbCtrl_GetVersion(void);

/***************************************************************************//**
 * Get the size of the UMB controller handle
 *
 * @param[in]       void
 * @return		    handle size
 ******************************************************************************/
DECL_DLL uint32 UmbCtrl_GetHandleSize(void);

/***************************************************************************//**
 * Initialize a UMB controller instance
 *
 * @param[in]       *pHandle        pointer to the handle
 * @param[in]       *pSensorCom     pointer to the protocol communication functions
 * @param[in]		addTimeout		additional timeout for communication [ms]
 * @return          UMB_CTRL_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_STATUS_T UmbCtrl_Init(UMB_CTRL_T* const pHandle, const UMB_CTRL_COM_FUNCTION_T* const pComFunction, const uint32 addTimeout);

/***************************************************************************//**
 * Deinitialize a UMB controller instance
 *
 * @param[in]       *pHandle        pointer to the handle
 * @return          UMB_CTRL_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_STATUS_T UmbCtrl_Deinit(UMB_CTRL_T* const pHandle);

/***************************************************************************//**
 * Get the device status
 *
 * @param[in]       *pHandle        pointer to the handle
 * @param[in]       toaddress       UMB address of the device (class id + device id)
 * @param[out]      *pStatus        pointer to the status of the device
 * @return          UMB_CTRL_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_STATUS_T UmbCtrl_GetDevStatus(UMB_CTRL_T* const pHandle, const UMB_ADDRESS_T toaddress,
										ERROR_STATUS_T* const pStatus);

/***************************************************************************//**
 * Get the device name
 *
 * @param[in]       *pHandle        pointer to the handle
 * @param[in]       toaddress       UMB address of the device (class id + device id)
 * @param[out]      *pDeviceName    pointer to the name of the device,
 *                                  must point to a memory area of 41 bytes
 * @return          UMB_CTRL_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_STATUS_T UmbCtrl_GetDevName(UMB_CTRL_T* const pHandle, const UMB_ADDRESS_T toaddress,
										str8 pDeviceName[41]);

/***************************************************************************//**
 * Get the number of UMB channels
 *
 * @param[in]       *pHandle        pointer to the handle
 * @param[in]       toaddress       UMB address of the device (class id + device id)
 * @param[out]      *pNumChannels   pointer to the number of UMB channels
 * @param[out]      *pNumBlocks		pointer to the number of blocks
 * @return          UMB_CTRL_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_STATUS_T UmbCtrl_GetNumChannels(UMB_CTRL_T* const pHandle, const UMB_ADDRESS_T toaddress,
										uint16* const pNumChannels, uint8* const pNumBlocks);

/***************************************************************************//**
 * Get the channel numbers in a block
 *
 * @param[in]       *pHandle        pointer to the handle
 * @param[in]       toaddress       UMB address of the device (class id + device id)
 * @param[in]       block			block
 * @param[out]      *pNumChannels   pointer to the number of UMB channels
 * @param[out]      *pChannels		pointer to the channel numbers,
 *									must point to a memory area of at least *pNumChannels * sizeof(uint16)
 * @return          UMB_CTRL_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_STATUS_T UmbCtrl_GetChannels(UMB_CTRL_T* const pHandle, const UMB_ADDRESS_T toaddress, const uint8 block,
										uint8* const pNumChannels, uint16 pChannels[100]);

/***************************************************************************//**
 * Get the number of UMB channels
 *
 * @param[in]       *pHandle        pointer to the handle
 * @param[in]       toaddress       UMB address of the device (class id + device id)
 * @param[in]       channel			channel number
 * @param[out]      *pChannelInfo	pointer to the channel info
 * @return          UMB_CTRL_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_STATUS_T UmbCtrl_GetChannelInfo(UMB_CTRL_T* const pHandle, const UMB_ADDRESS_T toaddress, const uint16 channel,
										UMB_CTRL_CHANNELINFO_T* const pChannelInfo);

/***************************************************************************//**
 * Get the measurement data
 *
 * @param[in]       *pHandle        pointer to the handle
 * @param[in]       toaddress       UMB address of the device (class id + device id)
 * @param[in]       numChannels		number of UMB channels to be requested
 * @param[in]       *pChannel		pointer to an array, which contains numChannels UMB channel numbers
 * @param[out]      *pMeasData      pointer to an array, which contains numChannels measurement data
 * @return          UMB_CTRL_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_STATUS_T UmbCtrl_GetMultiChannelData(UMB_CTRL_T* const pHandle, const UMB_ADDRESS_T toaddress, const uint8 numChannels, const uint16 pChannel[],
										MEAS_CHANNEL_VALUE_T pMeasData[]);

/***************************************************************************//**
 * Read data out of the memory of a device
 *
 * @param[in]       *pHandle        pointer to the handle
 * @param[in]       toaddress       UMB address of the device (class id + device id)
 * @param[in]       start           start address of the memory
 * @param[in]       length          number of bytes to be read out
 * @param[out]      *pData          pointer to the data, to which the memory data of the device is written to,
 *                                  must point to a memory area of at least 'length' bytes
 * @return          UMB_CTRL_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_STATUS_T UmbCtrl_ReadMem(UMB_CTRL_T* const pHandle, const UMB_ADDRESS_T toaddress, const uint16 start, const uint8 length,
										uint8 pData[]);

/***************************************************************************//**
 * Write data into the memory of a device
 *
 * @param[in]       *pHandle        pointer to the handle
 * @param[in]       toaddress       UMB address of the device (class id + device id)
 * @param[in]       start           start address of the memory
 * @param[in]       length          number of bytes to be written
 * @param[in]       *pData          pointer to the data, which is to be written into the memory of the device,
 *                                  must point to a memory area of at least 'length' bytes
 * @return          UMB_CTRL_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_STATUS_T UmbCtrl_WriteMem(UMB_CTRL_T* const pHandle, const UMB_ADDRESS_T toaddress, const uint16 start, const uint8 length, const uint8 pData[]);

/***************************************************************************//**
 * Reset a device
 *
 * @param[in]       *pHandle        pointer to the handle
 * @param[in]       toaddress       UMB address of the device (class id + device id)
 * @param[in]       reset           reset options
 * @return          UMB_CTRL_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_STATUS_T UmbCtrl_Reset(UMB_CTRL_T* const pHandle, const UMB_ADDRESS_T toaddress, const uint8 reset);

/***************************************************************************//**
 * Update the firmware of a device
 *
 * @param[in]       *pHandle        pointer to the handle
 * @param[in]       toaddress       UMB address of the device (class id + device id)
 * @param[in]       *fp             descriptor of the firmware file
 * @param[in]       reboot          'true': device will reboot after the firmware update
 *                                  'false': device won't reboot
 * @param[out]      *pUpdateProgress update status
 * @return          UMB_CTRL_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_STATUS_T UmbCtrl_UpdateFirmware(UMB_CTRL_T* const pHandle, const UMB_ADDRESS_T toaddress, const uint8 fileName[], const boolean reboot, volatile uint8* const pUpdateProgress);

/***************************************************************************//**
 * Get information of a firmware file
 *
 * @param[in]       *fp             descriptor of the firmware file
 * @param[out]      *pFileInfo      pointer to the file information
 * @return          ERROR_STATUS_T
 ******************************************************************************/
DECL_DLL UMB_CTRL_LIB_STATUS_T UmbCtrl_GetFwFileInfo(const uint8 fileName[], UMB_CTRL_FW_FILE_T* const pFileInfo);


#ifdef __cplusplus
}
#endif
#endif

////////////////////////////////////////////////////////////////////////////////
//                                 end of file                                //
////////////////////////////////////////////////////////////////////////////////
