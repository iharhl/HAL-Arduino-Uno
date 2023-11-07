#ifndef _LED_H
#define _LED_H

#include <avr/io.h>

void toggleLed(volatile uint8_t* port, int pin);

#endif