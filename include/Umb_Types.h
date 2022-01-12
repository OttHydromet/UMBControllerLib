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
 * @file            Umb_Types.h
 *
 * defines for types needed for UMB
 *
 ******************************************************************************/

#ifndef UMB_TYPES_H
#define UMB_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

 /**
 * Measurement Types
 */

 /* Typedefs for datatypes */
typedef uint8_t                 boolean;
typedef uint8_t                 str8;
typedef int8_t                  sint8;
typedef uint8_t                 uint8;
typedef int16_t                 sint16;
typedef uint16_t                uint16;
typedef int32_t                 sint32;
typedef uint32_t                uint32;
typedef uint64_t                uint64;
typedef int64_t                 sint64;

#if defined __STDC_IEC_559__ || defined _MSC_VER
    // IEC 559 defines float as 4 byte and double as 8 byte
    typedef float               float32;
    typedef double              float64;
#elif defined __GNUC__ && __RX__
    typedef float               float32;
#ifdef __RX_64BIT_DOUBLES__
    typedef double              float64;
#else
#error "Double is defined as only 4 bytes in size!"
#endif
#else
#error "Float and double are not defined!"
#endif

/* Standard return type for functions */
typedef uint8 Std_ReturnType;


/* Error value */
#ifndef E_OK
#define E_OK         0x00u
#endif

#ifndef E_NOT_OK
#define E_NOT_OK     0x01u
#endif


#ifdef __GNUC__
#define PACKED_STRUCT       _Pragma("pack(push,1)")
#define PACKED_STRUCT_END   _Pragma("pack(pop)")

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define IS_BIGENDIAN        1
#else
#define IS_BIGENDIAN        0
#endif

#ifdef __cplusplus
#define STATIC_ASSERT static_assert
#else
#define STATIC_ASSERT _Static_assert
#endif
#endif

#ifdef _MSC_VER
#define PACKED_STRUCT       __pragma(pack(push,1))
#define PACKED_STRUCT_END   __pragma(pack(pop))
#define IS_BIGENDIAN        0
#endif

#ifndef IS_BIGENDIAN
#error "Endianess is not defined!"
#endif

#if IS_BIGENDIAN
#error "Big-Endian is not supported!"
#endif

/**
 * UMB Error status
 **/
PACKED_STRUCT
typedef enum
{
    ERROR_STATUS_OK = 0x00,                   //!< 0x00, Command successful
    ERROR_STATUS_UNKNOWN_CMD = 0x10,          //!< 0x10, Unknown command
    ERROR_STATUS_INVALID_PARAM = 0x11,        //!< 0x11, Invalid parameter
    ERROR_STATUS_INVALID_HEADER = 0x12,       //!< 0x12, Invalid header version
    ERROR_STATUS_INVALID_VERC = 0x13,         //!< 0x13, Invalid command version
    ERROR_STATUS_INVALID_PW = 0x14,           //!< 0x14, Password mismatch
    ERROR_STATUS_INVALID_VALUE = 0x15,        //!< 0x15, Invalid value

    ERROR_STATUS_READ_ERR = 0x20,             //!< 0x20, Read error
    ERROR_STATUS_WRITE_ERR = 0x21,            //!< 0x21, Write error
    ERROR_STATUS_TOO_LONG = 0x22,             //!< 0x22, Too long
    ERROR_STATUS_INVALID_ADDRESS = 0x23,      //!< 0x23, Invalid address
    ERROR_STATUS_INVALID_CHANNEL = 0x24,      //!< 0x24, Invalid channel
    ERROR_STATUS_INVALID_CMD = 0x25,          //!< 0x25, Command impossible in mode
    ERROR_STATUS_UNKNOWN_CAL_CMD = 0x26,      //!< 0x26, Unknown adjustment command
    ERROR_STATUS_CAL_ERROR = 0x27,            //!< 0x27, Adjustment error
    ERROR_STATUS_BUSY = 0x28,                 //!< 0x28, Busy
    ERROR_STATUS_LOW_VOLTAGE = 0x29,          //!< 0x29, Low voltage
    ERROR_STATUS_HW_ERROR = 0x2A,             //!< 0x2A, Hardware fault
    ERROR_STATUS_MEAS_ERROR = 0x2B,           //!< 0x2B, Measurement error
    ERROR_STATUS_INIT_ERROR = 0x2C,           //!< 0x2C, Error during initialization
    ERROR_STATUS_OS_ERROR = 0x2D,             //!< 0x2D, Operating system error
    ERROR_STATUS_COM_ERROR = 0x2E,            //!< 0x2E, Internal Communication Error
    ERROR_STATUS_HW_SW_MISMATCH = 0x2F,       //!< 0x2F, Hardware and software version does not match

    ERROR_STATUS_E2_DEFAULT_KONF = 0x30,      //!< 0x30, Error, default E2 loaded
    ERROR_STATUS_E2_CAL_ERROR = 0x31,         //!< 0x31, Adjustment invalid
    ERROR_STATUS_E2_CRC_CONF_ERR = 0x32,      //!< 0x32, Config data CRC error
    ERROR_STATUS_E2_CRC_CAL_ERR = 0x33,       //!< 0x33, Adjustment data CRC error
    ERROR_STATUS_ADJ_STEP1 = 0x34,            //!< 0x34, Adjustment step 1
    ERROR_STATUS_ADJ_OK = 0x35,               //!< 0x35, Adjustment OK
    ERROR_STATUS_CHANNEL_OFF = 0x36,          //!< 0x36, Channel off
    ERROR_STATUS_SERVICE_MODE = 0x37,         //!< 0x37, Service mode active
    ERROR_STATUS_RESET_PENDING = 0x38,        //!< 0x38, Reset Pending
    ERROR_STATUS_ADJ_DEFAULT = 0x39,          //!< 0x39, Adjustment Reset, matches default values

    ERROR_STATUS_VALUE_OVERFLOW = 0x50,       //!< 0x50, Value over displayable range (+offset)
    ERROR_STATUS_VALUE_UNDERFLOW = 0x51,      //!< 0x51, Value under displayable range(+offset)
    ERROR_STATUS_CHANNEL_OVERRANGE = 0x52,    //!< 0x52, Physical value over range
    ERROR_STATUS_CHANNEL_UNDERRANGE = 0x53,   //!< 0x53, Physical value under range
    ERROR_STATUS_DATA_ERROR = 0x54,           //!< 0x54, Measurement data invalid
    ERROR_STATUS_MEAS_UNABLE = 0x55,          //!< 0x55, Measurement impossible
    ERROR_STATUS_CALC_ERROR = 0x56,           //!< 0x56, Calculation error (Nan, devision by zero)

    ERROR_STATUS_FLASH_CRC_ERR = 0x60,        //!< 0x60, Flash data CRC error
    ERROR_STATUS_FLASH_WRITE_ERR = 0x61,      //!< 0x61, Error writing flash
    ERROR_STATUS_FLASH_FLOAT_ERR = 0x62,      //!< 0x62, Invalid float value
    ERROR_STATUS_FLASH_ERR = 0x63,            //!< 0x63, Flash defective
    ERROR_STATUS_CONFIG_ERR = 0x64,           //!< 0x64, Configuration error

    ERROR_STATUS_UNKNOWN_ERR = (uint8)0xFF           //!< Unspecified error
} ERROR_STATUS_T;
PACKED_STRUCT_END

 /**
 * Measurement Types
 */

//! UMB channel value type
typedef enum
{
    VALUE_TYPE_CUR = 0x10,  //!< current value
    VALUE_TYPE_MIN = 0x11,  //!< minimum value
    VALUE_TYPE_MAX = 0x12,  //!< maximum value
    VALUE_TYPE_AVG = 0x13,  //!< average value
    VALUE_TYPE_SUM = 0x14,  //!< sum of values
    VALUE_TYPE_VCT = 0x15   //!< vectorial average
} MEAS_VALUE_TYPE_T;

//! UMB channel data types
typedef enum
{
    DATA_TYPE_U8 = 0x10,    //!< unsigned char
    DATA_TYPE_S8 = 0x11,    //!< signed char
    DATA_TYPE_U16 = 0x12,   //!< unsigned short
    DATA_TYPE_S16 = 0x13,   //!< signed short
    DATA_TYPE_U32 = 0x14,   //!< unsigned long
    DATA_TYPE_S32 = 0x15,   //!< signed long
    DATA_TYPE_F32 = 0x16,   //!< float
    DATA_TYPE_F64 = 0x17,   //!< double
} MEAS_DATA_TYPE_T;

//! UMB measurement values
PACKED_STRUCT
typedef union MEAS_VAL
{
    uint8 u8_val;
    sint8 s8_val;

    uint16 u16_val;
    sint16 s16_val;

    uint32 u32_val;
    sint32 s32_val;

    float32 f32_val;
    float64 f64_val;
} MEAS_VAL_T;
PACKED_STRUCT_END

//! Channel data
typedef struct
{
    uint16              ch_number;      //!< channel number
    MEAS_VAL_T          ch_value;       //!< current channel value
    MEAS_DATA_TYPE_T    ch_data_type;   //!< data type of the channel value
    ERROR_STATUS_T      ch_status;      //!< UMB status of the channel value
} MEAS_CHANNEL_VALUE_T;


/**
 * Umb Types
 */

//! UMB address
PACKED_STRUCT
typedef struct
{
    uint8 classId;
    uint8 deviceId;
} UMB_ADDRESS_T;
PACKED_STRUCT_END

#ifdef __cplusplus
}
#endif

#endif
