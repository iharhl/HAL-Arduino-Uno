CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Os -DF_CPU=16000000UL -mmcu=atmega328p

BUILD_DIR = build
SRC_DIR = src
OBJS = $(BUILD_DIR)/gpio.o $(BUILD_DIR)/pwm.o $(BUILD_DIR)/assert_handler.o

LINKER_FLAGS = -Wl,-Map,$(BUILD_DIR)/main.map

ifeq ($(shell uname -s),Darwin)
	PORT = /dev/tty.usbmodem11201
else
	PORT = COM3
endif


all: build $(OBJS)
	$(CC) $(CFLAGS) $(LINKER_FLAGS) $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.elf $(OBJS)
	$(OBJCOPY) -O ihex -R .eeprom $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.hex

$(BUILD_DIR)/gpio.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/gpio.c -o $(BUILD_DIR)/gpio.o

$(BUILD_DIR)/pwm.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pwm.c -o $(BUILD_DIR)/pwm.o

$(BUILD_DIR)/assert_handler.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/assert_handler.c -o $(BUILD_DIR)/assert_handler.o

flash:
	avrdude -c arduino -p atmega328p -P $(PORT) -U flash:w:$(BUILD_DIR)/main.hex

size:
	avr-size -C --mcu=atmega328p $(BUILD_DIR)/main.elf

cache-dump:
	avr-objdump -h led
	avr-objdump -S led

build:
	mkdir -p build

clean:
	rm -rf build/*

full: clean all flash
