## STM32F411VET6 Makefile
# Minimal, reproducible Makefile for arm-none-eabi toolchain

# Toolchain
CC := arm-none-eabi-gcc
CXX := arm-none-eabi-g++
AS := arm-none-eabi-as
OBJCOPY := arm-none-eabi-objcopy
SIZE := arm-none-eabi-size

# MCU flags
MCU := cortex-m4
FPU := fpv4-sp-d16
FLOAT_ABI := hard

# Directories
PROJECT_ROOT := .
CORE_DIR := Core
DRIVER_HAL_DIR := Drivers/STM32F4xx_HAL_Driver
DRIVER_CMSIS_DIR := Drivers/CMSIS
STARTUP_DIR := $(CORE_DIR)/Startup
BUILD_DIR := Debug

# Sources
C_SRCS := $(wildcard $(CORE_DIR)/Src/*.c) $(wildcard $(DRIVER_HAL_DIR)/Src/*.c)
CPP_SRCS := $(wildcard $(CORE_DIR)/Src/*.cpp)
ASM_SRCS := $(wildcard $(STARTUP_DIR)/*.s)

# Target
TARGET := f411vet6_with_motor_encoder_wihros
ELF := $(BUILD_DIR)/$(TARGET).elf
BIN := $(BUILD_DIR)/$(TARGET).bin
HEX := $(BUILD_DIR)/$(TARGET).hex

# Place object files under $(BUILD_DIR) preserving relative paths
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SRCS)) \
	$(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS)) \
	$(patsubst %.s,$(BUILD_DIR)/%.o,$(ASM_SRCS))

# Include paths
INCLUDES := -I$(CORE_DIR)/Inc \
	-I$(DRIVER_HAL_DIR)/Inc \
	-I$(DRIVER_CMSIS_DIR)/Include \
	-IDrivers/CMSIS/Device/ST/STM32F4xx/Include

# Compiler/Linker flags
CFLAGS := -DSTM32F411xE -mcpu=$(MCU) -mthumb -mfpu=$(FPU) -mfloat-abi=$(FLOAT_ABI) -O2 -Wall $(INCLUDES)
CXXFLAGS := $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS := -mcpu=$(MCU) -mthumb
LDSCRIPT := STM32F411VETX_FLASH.ld
LDFLAGS := -T$(LDSCRIPT) -mcpu=$(MCU) -mthumb -mfpu=$(FPU) -mfloat-abi=$(FLOAT_ABI) -specs=nosys.specs -Wl,--gc-sections

.PHONY: all clean
all: $(ELF) $(BIN) $(HEX)

$(ELF): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS)
	$(SIZE) $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

# Build rules: ensure object directories exist and compile
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

# Print some helpful info
info:
	@echo "Target ELF: $(ELF)"
	@echo "Objects:"
	@printf '%s\n' $(OBJS)
# Makefile for STM32F411VET6 project
# Toolchain
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size

# MCU and FPU
MCU=cortex-m4
FPU=fpv4-sp-d16
FLOAT-ABI=hard

# Directories
TARGET=f411vet6_with_motor_encoder_wihros
BUILD_DIR=Debug

OBJS=$(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SRCS)) \
	$(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS)) \
	$(patsubst %.s,$(BUILD_DIR)/%.o,$(ASM_SRCS))

# Output
DRIVER_HAL_DIR=Drivers/STM32F4xx_HAL_Driver
DRIVER_CMSIS_DIR=Drivers/CMSIS
STARTUP_DIR=$(CORE_DIR)/Startup
OBJS=$(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SRCS)) \
	$(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS)) \
	$(patsubst %.s,$(BUILD_DIR)/%.o,$(ASM_SRCS))
# Source files
C_SRCS=$(wildcard $(CORE_DIR)/Src/*.c) \
       $(wildcard $(DRIVER_HAL_DIR)/Src/*.c)
CPP_SRCS=$(wildcard $(CORE_DIR)/Src/*.cpp)
ASM_SRCS=$(wildcard $(STARTUP_DIR)/*.s)

# Include directories
INCLUDES=-I$(CORE_DIR)/Inc \
		 -I$(DRIVER_HAL_DIR)/Inc \
		 -I$(DRIVER_CMSIS_DIR)/Include \
		 -IDrivers/CMSIS/Device/ST/STM32F4xx/Include

# Linker script
LDSCRIPT=STM32F411VETX_FLASH.ld
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
CFLAGS=-DSTM32F411xE -mcpu=$(MCU) -mthumb -mfpu=$(FPU) -mfloat-abi=$(FLOAT-ABI) -O2 -Wall $(INCLUDES)
CXXFLAGS=$(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS=-mcpu=$(MCU) -mthumb
LDFLAGS=-T$(LDSCRIPT) -mcpu=$(MCU) -mthumb -mfpu=$(FPU) -mfloat-abi=$(FLOAT-ABI) -specs=nosys.specs -Wl,--gc-sections

# Output
TARGET=f411vet6_with_motor_encoder_wihros
BUILD_DIR=Debug

OBJS=$(C_SRCS:.c=.o) $(CPP_SRCS:.cpp=.o) $(ASM_SRCS:.s=.o)

# Rules
all: $(BUILD_DIR)/$(TARGET).elf


$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS)
	$(SIZE) $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(CORE_DIR)/Src/*.o
	rm -f $(DRIVER_HAL_DIR)/Src/*.o
	rm -f $(STARTUP_DIR)/*.o
	rm -f $(BUILD_DIR)/*.elf

.PHONY: all clean
