# Flags
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Os -DF_CPU=16000000UL -mmcu=atmega328p
CC_TEST = gcc
C_TEST_FLAGS = -g -Wall -Wextra -Wconversion -DDEBUG_SIM
LINKER_FLAGS = -Wl,-Map,$(BUILD_DIR)/main.map

# Targets
TARGET = main.elf
TEST_TARGET = test_main

# Main folders
BUILD_DIR = build
SRC_DIR = src
TEST_DIR = tests

# Source objects
SOURCES = $(wildcard $(SRC_DIR)/*.c)
INCLUDES = $(wildcard $(SRC_DIR)/*.h)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Source objects for unit testing
TEST_SOURCES = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
TEST_INCLUDES = $(wildcard $(SRC_DIR)/*.h)
TEST_OBJECTS = $(TEST_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/t_%.o)

# Unit test objects
UT_SOURCES = $(wildcard $(TEST_DIR)/*.c)
UT_INCLUDES = $(wildcard $(TEST_DIR)/*.h)
UT_OBJECTS = $(UT_SOURCES:$(TEST_DIR)/%.c=$(BUILD_DIR)/%.o)

# Ports to program the board
ifeq ($(shell uname -s),Darwin)
	PORT = /dev/tty.usbmodem11201
else
	PORT = COM3
endif

# Build target for HW board
$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LINKER_FLAGS) -o $@ $(OBJECTS)
	$(OBJCOPY) -O ihex -R .eeprom $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.hex

test: $(BUILD_DIR)/$(TEST_TARGET)

run_test:
	$(BUILD_DIR)/$(TEST_TARGET)

# Build target for unit testing
$(BUILD_DIR)/$(TEST_TARGET): $(TEST_OBJECTS) $(UT_OBJECTS)
	echo $(TEST_SOURCES)
	$(CC_TEST) $(C_TEST_FLAGS) -o $@ $(TEST_OBJECTS) $(UT_OBJECTS)

# Build source objects for HW board
$(OBJECTS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c $(INCLUDES) build
	$(CC) $(CFLAGS) -c $< -o $@

# Build source objects for unit tests
$(TEST_OBJECTS): $(BUILD_DIR)/t_%.o : $(SRC_DIR)/%.c $(INCLUDES) build
	$(CC_TEST) $(C_TEST_FLAGS) -c $< -o $@

# Build unit tests
$(UT_OBJECTS): $(BUILD_DIR)/%.o : $(TEST_DIR)/%.c $(UT_INCLUDES) build
	$(CC_TEST) $(C_TEST_FLAGS) -c $< -o $@

flash:
	avrdude -c arduino -p atmega328p -P $(PORT) -U flash:w:$(BUILD_DIR)/main.hex

size:
	avr-size -C --mcu=atmega328p $(BUILD_DIR)/main.elf

cache-dump:
	avr-objdump -h build/main.elf
	avr-objdump -S build/main.elf

build:
	mkdir -p build

clean:
	rm -rf build/*
