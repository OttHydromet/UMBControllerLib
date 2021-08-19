
# **The UMB Controller Library**

The UMB controller library implements a UMB controller, sending requests to UMB devices and processing their responses.
Some sample code is provided to help you integrating the library into your system.

The library is written in the C language and available as a static library for the following operating systems / architectures:

|            | **Windows**             | **Linux**             | **Linux / ARM**          |
| ---------- | ----------------------- | --------------------- | ------------------------ |
| **64 bit** | UmbControllerLib.lib    | libUmbController.a    | libUmbControllerArm_64.a |
| **32 bit** | UmbControllerLib_32.lib | libUmbController_32.a | libUmbControllerArm_32.a |

It does not use dynamic memory allocation.

For a detailed description see the manual in the docs folder.

LICENSE.md contains the license agreement.

Please note, that this is a beta version and not all of the commands specified by the UMB protocol are implemented yet.

# The UMB Protocol

The UMB protocol is an open binary protocol specified by the Lufft
company for the configuration and data retrieval of measuring devices.

The current version of the specification can be found in the download
area of ​​the homepage [www.Lufft.de](http://www.Lufft.de). The document
contains all information on the frame structure and timing as well as a
detailed description of all commands.


