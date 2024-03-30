CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Os -DF_CPU=16000000UL -mmcu=atmega328p

CC_TEST = gcc
C_TEST_FLAGS = -g -Wall -Wextra -Wconversion -DAVR_TEST

BUILD_DIR = build
SRC_DIR = src
OBJS = $(BUILD_DIR)/gpio.o \
	$(BUILD_DIR)/pwm.o \
	$(BUILD_DIR)/assert_handler.o \
	$(BUILD_DIR)/spi.o \
	$(BUILD_DIR)/adc.o
TEST_OBJS = $(BUILD_DIR)/avr_io_mock.o \
			$(BUILD_DIR)/test_gpio.o \
			$(BUILD_DIR)/test_pwm.o \
			$(BUILD_DIR)/test_assert_handler.o \
			$(BUILD_DIR)/test_trace.o \
			$(BUILD_DIR)/test_spi.o \
			$(BUILD_DIR)/test_adc.o \
LINKER_FLAGS = -Wl,-Map,$(BUILD_DIR)/main.map

ifeq ($(shell uname -s),Darwin)
	PORT = /dev/tty.usbmodem11201
else
	PORT = COM3
endif

all: build $(OBJS)
	$(CC) $(CFLAGS) $(LINKER_FLAGS) $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.elf $(OBJS)
	$(OBJCOPY) -O ihex -R .eeprom $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.hex

test: build $(TEST_OBJS)
	$(CC_TEST) $(C_TEST_FLAGS) tests/gpio_test.c $(TEST_OBJS) -o $(BUILD_DIR)/gpio_test

run_test:
	$(BUILD_DIR)/gpio_test

# Build for target
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c build
	$(CC) $(CFLAGS) -c $< -o $@

# Build for simulation
$(BUILD_DIR)/test_%.o: $(SRC_DIR)/%.c build
	$(CC_TEST) $(C_TEST_FLAGS) -c $< -o $@

# TODO: ...
$(BUILD_DIR)/avr_io_mock.o: tests/avr_io_mock.c build
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

full: clean all flash
