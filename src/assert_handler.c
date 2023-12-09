#include "assert_handler.h"
#include "gpio.h"

#ifndef AVR_TEST
#include <util/delay.h>
#endif

void blink_led(void)
{
    // Setup on-board LED
    // io_set_direction(13, GPIO_DIR_OUTPUT);

    // Infinitely blink
    while(1)
    {
        // TODO : fix write
        // digitalWrite(&PORTB, PORTB5, LOW);
        // _delay_ms(500);
        // digitalWrite(&PORTB, PORTB5, HIGH);
        // _delay_ms(500);
    }
}

void assert_handler(void)
{
    // TODO: set pins to low
    // TODO: trace
    blink_led();
}