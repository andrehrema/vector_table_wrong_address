# Description
This is an experimental project, and its main objective is to study the bare metal development for STM32 devices.
In the current state, it aims STM32F446RE uC, located in a Nucleo board.

# Requirements
- [STM32 Cube framework](https://github.com/STMicroelectronics/STM32CubeF4) installed.
- [ARM GNU toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads).

# Compilation
To successfully compile the project, modify the following variables in the build-project script:
- ARM_INCLUDES: points to the headers installed by the arm gnu toolchain;
- STM_FRAMEWORK_PATH: points to the STM32 framework;
- LIB_PATH: path to the ARM libraries

the compilation is executed with the following command:
```
cibuild/build-project 0 1
```
The 0 value is to not use HAL library, and 1 is to enable low level drivers.