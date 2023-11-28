#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "types.h"
#include "pwm.h"

int main(void)
{
    // Configure pin 6 (PD6) as output
    configurePin(6, OUTPUT);
    configurePin(11, OUTPUT);

    // Test
    // configurePin(A0, OUTPUT);
    
    PWM_init(6);
    PWM_init(11);

    while(1)
    {
        // digitalWrite(&PORTB, PORTB5, LOW);
        // _delay_ms(1000);
        // digitalWrite(&PORTB, PORTB5, HIGH);
        // _delay_ms(1000);
        PWM_send(6, 128);
        PWM_send(11, 128);
        _delay_ms(5);
        PWM_send(6, 64);
        PWM_send(11, 64);
        _delay_ms(5);
    }
}
