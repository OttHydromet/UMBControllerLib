# Content

[Change History - 2 -](#_Toc72400209)

[1 The UMB Protocol - 3 -](#_Toc72400210)

[2 The UMB Library - 3 -](#the-umb-library)

[3 Scope of Delivery - 4 -](#scope-of-delivery)

[4 Commissioning - 5 -](#commissioning)

[5 Usage - 5 -](#usage)

[5.1 System Connection - 5 -](#system-connection)

[5.2 Initialization - 8 -](#initialization)

[5.3 Test Programm - 9 -](#test-programm)

[6 Notes on Firmware Update - 10 -](#notes-on-firmware-update)

# Change History

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 18%" />
<col style="width: 69%" />
</colgroup>
<thead>
<tr class="header">
<th>Version</th>
<th>Datum</th>
<th>Änderungen</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>V0.1</td>
<td>12.03.2021</td>
<td>Initial Version</td>
</tr>
<tr class="even">
<td>V0.2</td>
<td>22.03.2021</td>
<td><p>Screenshots adjusted</p>
<p>Explanations to UMB Specification</p></td>
</tr>
<tr class="odd">
<td>V0.3</td>
<td>19.04.2021</td>
<td>64-bit versions of the library</td>
</tr>
<tr class="even">
<td>V0.4</td>
<td>06.05.2021</td>
<td>64-bit version for ARM</td>
</tr>
<tr class="odd">
<td>V0.5</td>
<td>20.05.2021</td>
<td>Table of supported UMB commands</td>
</tr>
</tbody>
</table>

# The UMB Protocol

The UMB protocol is an open binary protocol specified by the Lufft
company for the configuration and data retrieval of measuring devices.

The current version of the specification can be found in the download
area of ​​the homepage [www.Lufft.de](http://www.Lufft.de). The document
contains all information on the frame structure and timing as well as a
detailed description of all commands.

# The UMB Library

The library is written in the C language and is available for Windows
and Linux.

It does not use dynamic memory allocation.

The commands of the UMB protocol listed in Table 1 are implemented in
the library.

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 71%" />
<col style="width: 14%" />
</colgroup>
<thead>
<tr class="header">
<th><strong>&lt;cmd&gt;</strong></th>
<th><strong>Description</strong></th>
<th><strong>Library V0.4</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>20h</td>
<td>Hardware and software version</td>
<td></td>
</tr>
<tr class="even">
<td>21h</td>
<td>Read out EEPROM</td>
<td></td>
</tr>
<tr class="odd">
<td>22h</td>
<td>Program EEPROM</td>
<td></td>
</tr>
<tr class="even">
<td>23h</td>
<td>Online data request</td>
<td></td>
</tr>
<tr class="odd">
<td>24h</td>
<td>Offline data request</td>
<td></td>
</tr>
<tr class="even">
<td>25h</td>
<td>Reset / default</td>
<td></td>
</tr>
<tr class="odd">
<td>26h</td>
<td>Status request</td>
<td></td>
</tr>
<tr class="even">
<td>27h</td>
<td>Set time / date</td>
<td></td>
</tr>
<tr class="odd">
<td>28h</td>
<td>Read out time / date</td>
<td></td>
</tr>
<tr class="even">
<td>29h</td>
<td>Test command</td>
<td></td>
</tr>
<tr class="odd">
<td>2Ah</td>
<td>Monitor</td>
<td></td>
</tr>
<tr class="even">
<td>2Bh</td>
<td>Protocol change</td>
<td></td>
</tr>
<tr class="odd">
<td>2Ch</td>
<td>Last fault message</td>
<td></td>
</tr>
<tr class="even">
<td>2Dh</td>
<td>Device information</td>
<td></td>
</tr>
<tr class="odd">
<td>2Eh</td>
<td>Reset with delay</td>
<td></td>
</tr>
<tr class="even">
<td><strong>&lt;cmd&gt;</strong></td>
<td><strong>Description</strong></td>
<td><strong>Library V0.4</strong></td>
</tr>
<tr class="odd">
<td>2Fh</td>
<td>Multi-channel online data request</td>
<td></td>
</tr>
<tr class="even">
<td>30h</td>
<td>Set new device ID permanently<br />
(verc 1.0)</td>
<td></td>
</tr>
<tr class="odd">
<td>30h</td>
<td>Set new device ID temporarily<br />
(verc 1.1)</td>
<td></td>
</tr>
<tr class="even">
<td>36h</td>
<td>UMB-Tunnel</td>
<td></td>
</tr>
<tr class="odd">
<td>37h</td>
<td>Transfer Firmware</td>
<td></td>
</tr>
<tr class="even">
<td>38h</td>
<td>Transfer Binary Data</td>
<td></td>
</tr>
<tr class="odd">
<td></td>
<td></td>
<td></td>
</tr>
<tr class="even">
<td>40h – 7Fh</td>
<td>Reserved for device-specific commands<br />
(see device description)</td>
<td></td>
</tr>
<tr class="odd">
<td>80h – 8Fh</td>
<td>Reserved for development</td>
<td></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
</tr>
<tr class="odd">
<td>F0h</td>
<td>Program EEPROM with PIN</td>
<td></td>
</tr>
</tbody>
</table>

Table Commands of the UMB protocol, which are implemented by the library

A large number of device properties can be queried with the command
'Device information' (2Dh). So far, the sub-commands specified in Table
2 are supported.

|             |                                                          |                  |
|-------------|----------------------------------------------------------|------------------|
| **\<info>** | **Description**                                          | **Library V0.4** |
| 10h         | Device identification                                    |                  |
| 11h         | Device description                                       |                  |
| 12h         | Hardware and software version                            |                  |
| 13h         | Extended version info                                    |                  |
| 14h         | EEPROM size                                              |                  |
| 15h         | No. of channels available                                |                  |
| 16h         | Numbers of the channels                                  |                  |
| 17h         | Read number of device specific version information slots |                  |
| 18h         | Read device specific version information                 |                  |
| **\<info>** | **Description**                                          | **Library V0.4** |
| 20h         | Meas. variable of channel                                |                  |
| 21h         | Meas. range of channel                                   |                  |
| 22h         | Meas. unit of channel                                    |                  |
| 23h         | Data type of channel                                     |                  |
| 24h         | Meas. value type                                         |                  |
|             |                                                          |                  |
| 30h         | Complete channel info                                    |                  |
| 40h         | Number of IP interfaces                                  |                  |
| 41h         | IP Information                                           |                  |

Table 2 Sub-commands of the ‘Device information’ command, which are
supported by the library

# Scope of Delivery

The folder "**lufft**" contains all files that are required to use the
UMB library:

-   Software libraries for Windows and Linux / Linux on ARM

|            | **windows**             | **linux**             | **Linux / ARM**          |
|------------|-------------------------|-----------------------|--------------------------|
| **64 bit** | UmbControllerLib.lib    | libUmbController.a    | libUmbControllerArm_64.a |
| **32 bit** | UmbControllerLib_32.lib | libUmbController_32.a | libUmbControllerArm_32.a |

-   The header files to use the library:

> **UmbControllerLib.h**: Interface of the library
>
> **Umb_Types.h**: General type definitions

In the “**src**” folder you will find files with examples for connecting
the library to your own system:

-   **UmbCtrlTest.cpp**: Test program to illustrate how it works

-   **ComWin.c/.h**: Example implementation for connection under Windows

-   **ComLinux.c/.h**: Example implementation for connection under Linux

The "**win**" folder contains non-Lufft files that are used in the test
program or in the example implementations under Windows. The terms of
use specified in the respective source files must be observed here.

The “**examples**” folder contains an example for installing the library
on a RaspberryPi. Further examples are planned.

# Commissioning

To use the UMB library, the two header files Umb_Types.h and
UmbControllerLib.h must be copied into your own project.

Dependent on the system in use (Windows, Linux, Linux on ARM) the
respective library is required, see also chapter 3.

The installation instructions for a RaspberryPi can be read separately
in the README.txt file in the /examples/RaspberryPi directory.

# Usage

The current functional scope of the library can be found in the
interface file UmbControllerLib.h.

## System Connection

The serial interface is controlled via function pointers that are
defined in the UMB_CTRL_COM_FUNCTION_T structure, see Figure 1.

<img src="./media/image2.png" style="width:6.29931in;height:2.73542in" />

Figure 1 Structure with function pointers for controlling the serial
interface

The function pointers (\*pfnInit) and (\*pfnDeinit) are optional and
e.g. can be used to open or close the serial interface. However, if this
is already done elsewhere, the two function pointers can also be set to
NULL.

All other function pointers are mandatory and must be implemented.

The function pointers (\*pfnUse) und (\*pfnUnuse) are intended for the
protection of variables or code segments by semaphores. In the current
example implentations these functions do not include active code.

The handle \*pUserHandle can be used to pass user-specific data on to
the callback functions. In the example implementations comWin.cpp and
ComLinux.cpp, all data that are required during operation are summarized
in a structure COM_HANDLE_T. \*pUserHandle points to the address of such
a data record, which means that this data is then available in the
callback functions. Figure 2 shows the initialization of a
\*pUserHandle, Figure 3 the subsequent application.

<img src="./media/image3.png" style="width:6.29931in;height:1.86806in" />

Figure 2 Initialization of a \*pUserHandle

<img src="./media/image4.png" style="width:6.10053in;height:2.80858in" />

Figure 3 Usage of a \*pUserHandle

The modules ComLinux.cpp/.h and ComWin.cpp/.h show examples of how the
assignment of these function pointers can be implemented:

The control of the serial interface is implemented directly in ComLinux,
whereas ComWin uses third-party software (SerialPort.h) for which only
the wrapper functions compatible with the UMB library are provided, see
also Figure 4.

<img src="./media/image5.png" style="width:10.90625in;height:4.80347in" />

Figure 4 Implementation examples for controlling the serial interface:  
left: Example for Linux, manual implementation  
right: Example for Windows, usage of already existing implementation

## Initialization

The initialization of the UMB library comprises 3 points:

-   Allocation of the function pointers to control the serial interface

> For the sake of clarity, it is best to assign the required function
> pointers in a separate function defined by the user, see section 5.1.

-   Provision of the handle

> The UMB library does not use dynamic memory allocation. Therefore, the
> user must provide the memory for the library instances used.
>
> This handle is required when calling all other functions of the UMB
> library.

-   Calling the initialization function of the library

> The handle and the variable that contains the function pointers, must
> be given to the initialization function UmbCtrl_Init().

Figure 5 shows an example of the initialization sequence, Figure 6 a
query of the device name and the device status.

<img src="./media/image6.png" style="width:5.3588in;height:3.55031in" />

Figure 5 Initialization of the UMB library

<img src="./media/image7.png" style="width:4.66707in;height:4.63373in" />

Figure 6 Query of device name and device status

## Test Programm

The test program in UmbCtrlTest.cpp shows an example of how to use the
UMB Controller library. Before using the test program, all places marked
with 'TODO' in the main() program must be adapted to your own test
system. These are

-   Preprocessor definition \_USE_NCURSES, in order to be able to use
    the graphical progress display for the update function under Linux
    (for more details see below)

> #define \_USE_NCURSES

-   Used serial interface, e. g.

> char serialIf\[\] = { "3" };
>
> Note:
>
> Under Linux, the entire path of the serial interface must be specified
> here, e.g.
>
> char serialIf\[\] = { "/dev/tty03" };

-   Baud rate of the serial interface, e. g.

> comConfig.baudrate = 19200;

-   UMB address of the UMB device to be used for communication, e.g.

> umbAddress.deviceId = 0x01; // device id: 1
>
> umbAddress.classId = 0x70; // class id: 7 = weather station

-   Path and name of the firmware file, e.g.

> char fileName\[\] = {
> "C:\\\\Projekte\\\\UmbController\\\\WS100_update.bin" };

The functions that have been commented out (see Figure 7) are best
transferred into the test program individually and as required in order
to become familiar with the respective functionality.

<img src="./media/image8.png" style="width:2.94192in;height:1.31678in" />

Figure 7 Example functions for using the UMB library

**About the preprocessor definition_USE_NCURSES**

The example implementation firmwareUpdate() uses a graphical
representation of the update progress, which requires the ncurses
package under Linux. This must be installed manually e. g. on a
RaspberryPi, since it is not preinstalled via raspbian-stretch-lite.

Instructions for this can be found in the README.txt file in the
/examples/RaspberryPi directory.

If this progress display is to be used, the preprocessor definition
\_USE_NCURSES must be set after the ncurses package is installed. If, on
the other hand, this instruction is commented out, a simple progress
display is used instead of the graphical one, which does not require any
further packages.

# Notes on Firmware Update

Older UMB devices such as WSx00, Ventus, Anacon etc. use an update file
in .mot format. These cannot be transferred to a device via the UMB
protocol, but only via Hexload.

Therefore, for the new generation of UMB devices such as MARWIS, WS1000,
WS100, SHM31 and others the .bin file format was defined, which also
enables a firmware update via UMB.

-   Firmware updates via the UMB protocol are only possible for UMB
    devices whose update file is in .bin format
