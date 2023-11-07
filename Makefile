CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Os -DF_CPU=16000000UL -mmcu=atmega328p

BUILD_DIR = build
SRC_DIR = src

OBJS = $(BUILD_DIR)/gpio.o

LINKER_FLAGS = -Wl,-Map,$(BUILD_DIR)/main.map

all: build $(OBJS)
	$(CC) $(CFLAGS) $(LINKER_FLAGS) $(SRC_DIR)/main.c -o $(BUILD_DIR)/main $(OBJS)
	$(OBJCOPY) -O ihex -R .eeprom $(BUILD_DIR)/main $(BUILD_DIR)/main.hex

$(BUILD_DIR)/gpio.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/gpio.c -o $(BUILD_DIR)/gpio.o

flash:
	avrdude -c arduino -p atmega328p -P COM3 -U flash:w:$(BUILD_DIR)/main.hex

erase:
	avrdude -c arduino -p atmega328p -P COM3 -e

size:
	avr-size led

cache-dump:
	avr-objdump -h led
	avr-objdump -S led

build:
	mkdir -p build

clean:
	rm -rf build/*
