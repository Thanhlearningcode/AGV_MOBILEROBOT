STM32F411VET6 Project - Build Instructions

This repo contains firmware for the STM32F411VET6 (HAL + CMSIS). The Makefile builds with arm-none-eabi toolchain and places all object files under the `Debug/` directory preserving source-relative structure.

Prerequisites
- arm-none-eabi-gcc, arm-none-eabi-g++, arm-none-eabi-objcopy, arm-none-eabi-size must be installed and on PATH.

Quick build

```bash
# from project root
make clean
make -j$(nproc)
STM32F411VET6 Project - Build & Flash Instructions

This repo contains firmware for the STM32F411VET6 (HAL + CMSIS). The provided Makefile builds with the arm-none-eabi toolchain and places object files under the `Debug/` directory while preserving source-relative paths.

Prerequisites
- GNU Make (make)
- arm-none-eabi toolchain (gcc, g++, objcopy, size). On Debian/Ubuntu you can install via:

```bash
sudo apt-get update
sudo apt-get install -y gcc-arm-none-eabi binutils-arm-none-eabi gdb-multiarch
```

- One of the flashing tools below depending on your programmer:
	- OpenOCD (for ST-Link or other adapters)
	- stlink (st-flash) from https://github.com/stlink-org/stlink
	- STM32CubeProgrammer (`stm32cubeprog`) from ST (GUI + CLI)

Quick build

```bash
# from project root
make clean
make -j$(nproc)
```

Build artifacts
- `Debug/f411vet6_with_motor_encoder_wihros.elf` - linked ELF
- `Debug/f411vet6_with_motor_encoder_wihros.bin` - raw binary
- `Debug/f411vet6_with_motor_encoder_wihros.hex` - Intel HEX

Flash the board (examples)

1) Using st-flash (ST-Link v1/v2/v2-1)

```bash
# Erase, write binary and reset
st-flash --reset write Debug/f411vet6_with_motor_encoder_wihros.bin 0x8000000
```

2) Using OpenOCD + telnet (ST-Link)

Start OpenOCD (adjust interface/target if needed):

```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

In another terminal use telnet or the `openocd` telnet port to flash:

```bash
# connect via telnet (127.0.0.1:4444) and run:
telnet 127.0.0.1 4444
> reset halt
> flash write_image erase Debug/f411vet6_with_motor_encoder_wihros.elf 0x08000000
> reset run
> exit
```

3) Using STM32CubeProgrammer CLI (`stm32cubeprog`)

```bash
# Example: connect with ST-Link, program ELF (or BIN+address)
stm32cubeprog --connect --port=SWD --write Debug/f411vet6_with_motor_encoder_wihros.elf --start
```

Verify the flash

- Option A: Use `arm-none-eabi-objdump` or `readelf` to inspect the ELF.
- Option B: Use `openocd` or `stm32cubeprog` to read the first bytes back and compare a checksum.

Troubleshooting
- If the programmer can't connect: check USB, cable, drivers (on Linux you may need udev rules for ST-Link).
- If you see a CRC/verify error, try erasing fully before writing.
- If build fails with missing CMSIS/device headers: ensure `Makefile` contains the correct include path to `Drivers/CMSIS/Device/ST/STM32F4xx/Include` and `-DSTM32F411xE` is set.

Advanced notes
- The Makefile defines `STM32F411xE` so the CMSIS device header selects STM32F411 series.
- To change optimization or debugging flags, edit `CFLAGS`/`CXXFLAGS` in the `Makefile`.
- If you prefer a `make flash` target, I can add OpenOCD/st-flash commands to the Makefile (tell me which programmer you use).

If you want, tell me which programmer (ST-Link v2, v3, J-Link, etc.) you have and I will add a ready-to-use `make flash` target for it.
