#include "led.h"
#include <util/delay.h>

void toggleLed(volatile uint8_t* port, int pin)
{
    // Set PORTB5
    *port |= (1 << pin);

    // Delay
    _delay_ms(1000);

    // Reset
    *port &= ~(1 << pin);

    // Delay
    _delay_ms(1000);
}