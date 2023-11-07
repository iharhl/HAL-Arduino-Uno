#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "types.h"

int main(void)
{
    // Configure pin 5 (LED) as output
    configurePin(&DDRB, DDB5, OUTPUT);

    while(1)
    {
        digitalWrite(&PORTB, PORTB5, LOW);
        _delay_ms(1000);
        digitalWrite(&PORTB, PORTB5, HIGH);
        _delay_ms(1000);
    }
}
