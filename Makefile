all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o led.c
	avr-gcc -o led.bin led.o
	avr-objcopy -O ihex -R .eeprom led.bin led.hex
	avrdude -c arduino -p atmega328p -P COM3 -U flash:w:led.hex

size:
	avr-size --format=SysV led.bin