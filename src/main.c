#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

int main(void)
{
    // Configure pin 5 (LED) as output
    DDRB |= (1 << DDB5);

    while(1)
    {
        toggleLed(&PORTB, PORTB5);
    }
}
