#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = DDRB | (1 << DDB5);

    while(1)
    {
        // set PORTB5
        PORTB = PORTB | (1 << PORTB5);

        // delay
        _delay_ms(1000);

        // unset
        PORTB = PORTB & ~(1 << PORTB5);

        // delay
        _delay_ms(1000);
    }
}