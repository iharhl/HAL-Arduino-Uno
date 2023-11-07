#include "gpio.h"

void configurePin(volatile uint8_t* data_direction_register, uint8_t bit, IO_config_t setting)
{
    if (setting == INPUT)
    {
        *data_direction_register &= ~(1 << bit);
    } else {
        *data_direction_register |= (1 << bit);
    }
}

void digitalWrite(volatile uint8_t* port, uint8_t pin, digital_write_t value)
{
    if (value == LOW)
    {
        *port &= ~(1 << pin);
    } else {
        *port |= (1 << pin);
    }
}