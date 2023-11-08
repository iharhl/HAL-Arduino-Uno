#include "gpio.h"

// -> TODO
//
void _configureRegister(volatile uint8_t* data_direction_register, uint8_t bit, IO_config_t setting)
{
    if (setting == INPUT)
    {
        *data_direction_register &= ~(1 << bit);
    } else {
        *data_direction_register |= (1 << bit);
    }
}

void configurePin(uint8_t pin, IO_config_t setting)
{
    switch (pin)
    {
    case 0:
        _configureRegister(&DDRD, PD0, setting);
        break;
    case 1:
        _configureRegister(&DDRD, PD1, setting);
        break;
    case 2:
        _configureRegister(&DDRD, PD2, setting);
        break;
    case 3:
        _configureRegister(&DDRD, PD3, setting);
        break;
    case 4:
        _configureRegister(&DDRD, PD4, setting);
        break;
    case 5:
        _configureRegister(&DDRD, PD5, setting);
        break;
    case 6:
        _configureRegister(&DDRD, PD6, setting);
        break;
    case 7:
        _configureRegister(&DDRD, PD7, setting);
        break;
    case 8:
        _configureRegister(&DDRB, PB0, setting);
        break;
    case 9:
        _configureRegister(&DDRB, PB1, setting);
        break;
    case 10:
        _configureRegister(&DDRB, PB2, setting);
        break;
    case 11:
        _configureRegister(&DDRB, PB3, setting);
        break;
    case 12:
        _configureRegister(&DDRB, PB4, setting);
        break;
    case 13:
        _configureRegister(&DDRB, PB5, setting);
        break;
    /* Pins 14 till 19 are analog */
    case 14:
        _configureRegister(&DDRC, PC0, setting);
        break;
    case 15:
        _configureRegister(&DDRC, PC1, setting);
        break;
    case 16:
        _configureRegister(&DDRC, PC2, setting);
        break;
    case 17:
        _configureRegister(&DDRC, PC3, setting);
        break;
    case 18:
        _configureRegister(&DDRC, PC4, setting);
        break;
    case 19:
        _configureRegister(&DDRC, PC5, setting);
        break;
    default:
        // TODO
        break;
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