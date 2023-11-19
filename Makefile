CC = arm-none-eabi-gcc
OC = arm-none-eabi-objcopy
OS = arm-none-eabi-size

TARGET = stepper-driver
MCU_SPEC = cortex-m4

SRC_DIR = ./src
BUILD_DIR = build

DEVICE := stm32f446xx
LD_SCRIPT = $(DEVICE).ld

# debug build?
DEBUG = 1

WARNING_FLAGS = -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion -Wformat-truncation -Wconversion

COREFLAGS = -mcpu=$(MCU_SPEC) -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb-interwork -mlittle-endian

CFLAGS = -c $(COREFLAGS) \
		  $(INCLUDE_PATHS) $(MICROCONTROLLER_FLAG) -DUSE_FULL_LL_DRIVER \
		  -ffunction-sections -fdata-sections -fno-common

LFLAGS = -T$(LD_SCRIPT) --specs=nano.specs  --specs=nosys.specs \
   		 -Wl,-Map=$(BUILD_DIR)/$(TARGET).map $(COREFLAGS) \
		 $(LIB_PATH) -Wl,--gc-sections

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
OBJS += $(BUILD_DIR)/startup_$(DEVICE).o

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

.PHONY: clean docs

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(LFLAGS)  $^ -o $@
	$(OC) -O ihex $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex
	$(OC) -O binary $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

build/startup_$(DEVICE).o: src/link_to_startup_$(DEVICE).s
	$(CC) $(CFLAGS)  -T$(LD_SCRIPT) $< -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS)  -T$(LD_SCRIPT) $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*

docs:
#	doxygen Doxyfile
