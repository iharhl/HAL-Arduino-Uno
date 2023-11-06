CC= avr-gcc
OBJCOPY= avr-objcopy

all:
	$(CC) -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o led.c
	$(CC) -Wl,-Map,led.map -o led led.o
	$(OBJCOPY) -O ihex -R .eeprom led led.hex

flash:
	avrdude -c arduino -p atmega328p -P COM3 -U flash:w:led.hex

size:
	avr-size led

stuff:
	avr-objdump -h led
	avr-objdump -S led