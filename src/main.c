#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "types.h"
#include "pwm.h"

int main(void)
{
    // Configure pin 5 (LED) as output
    // configurePin(&DDRB, DDB5, OUTPUT);

    // Configure pin as PWM output
    DDRD |= (1<<PD6);

    while(1)
    {
        // digitalWrite(&PORTB, PORTB5, LOW);
        // _delay_ms(1000);
        // digitalWrite(&PORTB, PORTB5, HIGH);
        // _delay_ms(1000);
        sendPWM(0.2f);
        _delay_ms(5);
        sendPWM(0.8f);
        _delay_ms(5);
    }
}
