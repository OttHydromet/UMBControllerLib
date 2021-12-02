
# **The UMB Controller Library**

The UMB controller library implements a UMB controller, sending requests to UMB devices and processing their responses.
Some sample code is provided to help you integrating the library into your system.

The library is written in the C language and available as a dynamic library for the following operating systems / architectures:

|            | **Windows**                                        | **Linux**                 | **Linux / ARM**              |
| ---------- | -------------------------------------------------- | ------------------------- | ---------------------------- |
| **64 bit** | UmbControllerLib.dll<br>UmbControllerLib.lib       | libUmbControllerLib.so    | libUmbControllerLibArm_64.so |
| **32 bit** | UmbControllerLib_32.dll<br>UmbControllerLib_32.lib | libUmbControllerLib_32.so | libUmbControllerLibArm_32.so |

The library itself does not use dynamic memory allocation. For a detailed description see the manual in the docs folder.

[LICENSE](LICENSE.md) contains the license agreement.

Please note, that this is a beta version and not all of the commands specified by the UMB protocol are implemented yet.

# Usage

A [CMakeLists](CMakeLists.txt) file is provided foreasy integration into existing projects. It also includes an example project that may be used as a basis for new projects. To compile the example run the following commands:

```Bash
cmake -B build \ 
cmake --build build
```

# The UMB Protocol

The UMB protocol is an open binary protocol specified by the Lufft
company for the configuration and data retrieval of measuring devices.

The current version of the specification can be found in the download
area of ​​the homepage [www.Lufft.de](http://www.Lufft.de). The document
contains all information on the frame structure and timing as well as a
detailed description of all commands.
