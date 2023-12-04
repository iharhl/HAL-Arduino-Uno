#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "types.h"
#include "pwm.h"

int main(void)
{
    // Configure pin 6 (PD6) as output
    // configurePin(9, OUTPUT);
    // configurePin(10, OUTPUT);
    // configurePin(3, OUTPUT);
    io_set_direction(9, IO_DIR_OUTPUT);
    io_set_direction(10, IO_DIR_OUTPUT);
    io_set_direction(3, IO_DIR_OUTPUT);

    PWM_init(3);

    while(1)
    {
        PWM_send(3, 50);
        io_set_drive(9, IO_HIGH);
        // PWM_16bit_send(9, 0xEFFF);
        // PWM_16bit_send(10, 0xEFFF);
        _delay_ms(5);
        PWM_send(3, 200);
        io_set_drive(9, IO_LOW);
        // PWM_16bit_send(9, 0x000A);
        // PWM_16bit_send(10, 0x000A);
        _delay_ms(5);
    }
}
