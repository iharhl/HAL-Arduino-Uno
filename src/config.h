#ifndef CONFIG_H_
#define CONFIG_H_

#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#if F_CPU != 16000000UL
#undef F_CPU
#define F_CPU 16000000UL
#endif

#define EEPROM_SIZE 1024

#endif