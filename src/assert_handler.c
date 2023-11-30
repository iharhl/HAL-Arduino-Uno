#include "assert_handler.h"
#include "gpio.h"
#include "avr/io.h"

void assert_handler(void)
{
    // TODO: set pins to low
    // TODO: trace
    blink_led();
}

static void blink_led(void)
{
    // Setup on-board LED
    configurePin(13, OUTPUT);

    while(1)
    {
        // TODO
        digitalWrite(&PORTB, PORTB5, LOW);
        _delay_ms(500);
        digitalWrite(&PORTB, PORTB5, HIGH);
        _delay_ms(500);
    }
}