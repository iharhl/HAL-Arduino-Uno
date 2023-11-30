#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "types.h"
#include "pwm.h"

int main(void)
{
    // Configure pin 6 (PD6) as output
    configurePin(9, OUTPUT);
    configurePin(10, OUTPUT);
    configurePin(3, OUTPUT);

    // Test
    // configurePin(A0, OUTPUT);
    PWM_init(3);
    PWM_init(3);
    PWM_16bit_init(9);
    PWM_16bit_init(10);

    while(1)
    {
        // digitalWrite(&PORTB, PORTB5, LOW);
        // _delay_ms(1000);
        // digitalWrite(&PORTB, PORTB5, HIGH);
        // _delay_ms(1000);
        PWM_16bit_send(9, 0xEFFF);
        PWM_16bit_send(10, 0xEFFF);
        _delay_ms(5);
        PWM_16bit_send(9, 0x000A);
        PWM_16bit_send(10, 0x000A);
        _delay_ms(5);
    }
}
