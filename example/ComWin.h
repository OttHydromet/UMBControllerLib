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
 * @file            ComWin.h
 *
 * communication functions for UMB ctrl library (windows)
 *
 ******************************************************************************/

#ifndef COM_WIN_H_
#define COM_WIN_H_

#include "UmbControllerLib.h"

typedef struct
{
	char* serialIf;
	uint32 baudrate;
} COM_CONFIG_T;

UMB_CTRL_COM_FUNCTION_T* ComFunctionInit(COM_CONFIG_T* pConfig);
bool ComFunctionDeinit(UMB_CTRL_COM_FUNCTION_T* pComFunction);

#endif /* COM_WIN_H_ */
