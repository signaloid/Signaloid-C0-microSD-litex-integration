# Signaloid C0-microSD Firmware: Blink with UART
This is an example C based firmware for the default target design of the Signaloid C0-microSD, as defined in the [LiteX-Boards](https://github.com/litex-hub/litex-boards) repository.

The firmware implements a "blink" example, with UART serial communication support.
- Blinking Signaloid C0-microSD on-board red & green LEDs every 500ms.
- Printing the turned-on LED identifier (`r`: red, `g`: green). 
- Echoing the UART `tx` bytes on `rx`.

## Dependencies
Building the firmware requires that you have already installed the [RISC-V GNU Toolchain](https://github.com/riscv/riscv-gnu-toolchain) for RV32IM ISA extension. It assumes that it is installed in the default location, `opt/riscv32im/bin` on the host machine. If this is not the case, you can change its path in the `config.mk` file, on the `CROSS_COMPILE_PATH` variable. Also, make sure that the `DEVICE` variable in the `config.mk` file is set to the correct device path (follow the [Identify the Signaloid C0-microSD](https://c0-microsd-docs.signaloid.io/guides/identify-c0-microsd) guide).

## Getting Started
### Prerequisites
You must have already built the Signaloid C0-microSD gateware for the firmware to reference hardware support libraries. If you have already built the gateware, you can skip this step. To build the gateware and supporting libraries you can run the following commands:

Prepare the environment, if needed, and build the gateware. Run this in the project's root directory.
```sh
make gateware
```

### Makefiles
There is a dedicated Makefile for the firmware needs, which is located in the `firmware/` directory. It is included in the main Makefile, so you can run the commands from both the `firmware/` and the project's root directory.

Build the firmware. Run this in the project's `firmware/` directory.
```sh
make
```
or  
Run this in the project's root directory.
```sh
make firmware
```

Flash the firmware. This also builds the firmware, if there are changes. Make sure that the `DEVICE` variable in the `config.mk` file is set to the correct device path. Run this in the project's `firmware/` directory.
```sh
make flash
```
or  
Run this in the project's root directory.
```sh
make flash-firmware
```

Clean the build files. Run this in the project's `firmware/` directory.
```sh
make clean
```
or  
Run this in the project's root directory.
```sh
make clean-firmware
```

Print the variables used in the Makefile. Run this in the project's `firmware/` directory.
```sh
make print-vars
```
or  
Run this in the project's root directory.
```sh
make print-vars-firmware
```

## Firmware Binary
The firmware binary is stored in the `build/signaloid_c0_microsd/software/` directory with the name `signaloid_c0_microsd_firmware.bin`.

## Serial
The serial port is used for communication with the Signaloid C0-microSD. It is connected to the Signaloid C0-microSD's platform serial pins. Serial communication can be configured in the following way:

**Baudrate:** 115200

**Pins used:**
- `tx`=`A4|SD_CMD`
- `rx`=`B3|SD_CLK`

Serial communication can be accessed using `screen` on linux, or other similar tools.
```sh
screen /dev/ttyACM0 115200
```

## Execution description
The firmware binary is flashed using the Signaloid C0-microSD-toolkit through `make flash` or `make flash-firmware` on a specific address (USER_DATA_OFFSET: 0x200000) of the on-board SPI Flash (see [Bootloader Addressing](https://c0-microsd-docs.signaloid.io/hardware-overview/bootloader-addresssing.html)). This address is set as the `cpu_reset_address` in the target design script. Hence, when the Signaloid C0-microSD bitstream is loaded by the bootloader, the SoC will start executing from this address.

The entry point of the Signaloid C0-microSD firmware is the `_start` symbol, as defined by `linker.ld`. The `_start` symbol is defined in `build/signaloid_c0_microsd/software/core_libs/crt0.S`. `crt0.s` is an assembly file located at the path defined in the `CPU_DIRECTORY` variable from the `build/signaloid_c0_microsd/software/include/generated/variables.mak` file. It is responsible for:
- Setting the stack pointer
- Initializing the isr and exception vectors
- Initializing the global pointer
- Initializing the data section, by copying the rodata section
- Initializing the bss section
- Calling the C startup routine `main`

The execution continues as normal on the `main` function.

> [!NOTE]
> There is no instruction caching in this design. The whole SRAM (128kiB) is used for the data section of the application. All instructions are sequentially fetched from the on-board SPI Flash.
