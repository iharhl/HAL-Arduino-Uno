#include "gpio.h"

/* Get a port number based on pin number */
static inline uint8_t get_io_port(pin_e pin)
{
    if (pin >= 0 && pin < 8)
        return 0; // DDRD or PORTD
    else if (pin >= 8 && pin < 14)
        return 1; // DDRB or PORTB
    else if (pin >= 14 && pin < 20)
        return 2; //DDRC or PORTC
}

static inline uint8_t get_pin_bit(pin_e pin)
{
    if (pin >= 0 && pin < 8)
        return pin;
    else if (pin >= 8 && pin < 14)
        return pin-8;
    else if (pin >= 14 && pin < 20)
        return pin-14;
}

// Registers
static volatile uint8_t* const port_dir_regs[PORT_NUM] = { &DDRD, &DDRB, &DDRC }; // data direction registers
static volatile uint8_t* const port_drive_regs[PORT_NUM] = { &PORTD, &PORTB, &PORTC }; // data register

// static inline void _configureRegister(volatile uint8_t* data_direction_register, uint8_t bit, io_dir_e setting)
// {
//     if (setting == INPUT)
//     {
//         *data_direction_register &= ~(1 << bit);
//     } else {
//         *data_direction_register |= (1 << bit);
//     }
// }

// void configurePin(uint8_t pin, io_dir_e setting)
// {
//     switch (pin)
//     {
//     case 0:
//         _configureRegister(&DDRD, PD0, setting);
//         break;
//     case 1:
//         _configureRegister(&DDRD, PD1, setting);
//         break;
//     case 2:
//         _configureRegister(&DDRD, PD2, setting);
//         break;
//     case 3:
//         _configureRegister(&DDRD, PD3, setting);
//         break;
//     case 4:
//         _configureRegister(&DDRD, PD4, setting);
//         break;
//     case 5:
//         _configureRegister(&DDRD, PD5, setting);
//         break;
//     case 6:
//         _configureRegister(&DDRD, PD6, setting);
//         break;
//     case 7:
//         _configureRegister(&DDRD, PD7, setting);
//         break;
//     case 8:
        // _configureRegister(&DDRB, PB0, setting);
//         break;
//     case 9:
//         _configureRegister(&DDRB, PB1, setting);
//         break;
//     case 10:
//         _configureRegister(&DDRB, PB2, setting);
//         break;
//     case 11:
//         _configureRegister(&DDRB, PB3, setting);
//         break;
//     case 12:
//         _configureRegister(&DDRB, PB4, setting);
//         break;
//     case 13:
//         _configureRegister(&DDRB, PB5, setting);
//         break;
//     /* Pins 14 till 19 are analog */
//     case 14:
//         _configureRegister(&DDRC, PC0, setting);
//         break;
//     case 15:
//         _configureRegister(&DDRC, PC1, setting);
//         break;
//     case 16:
//         _configureRegister(&DDRC, PC2, setting);
//         break;
//     case 17:
//         _configureRegister(&DDRC, PC3, setting);
//         break;
//     case 18:
//         _configureRegister(&DDRC, PC4, setting);
//         break;
//     case 19:
//         _configureRegister(&DDRC, PC5, setting);
//         break;
//     default:
//         // TODO
//         break;
//     }
// }

void io_set_direction(pin_e pin, io_dir_e direction)
{
    const uint8_t port = get_io_port(pin);
    const uint8_t pin_bit = get_pin_bit(pin);
    switch (direction)
    {
    case IO_DIR_INPUT:
        *port_dir_regs[port] &= ~(1 << pin_bit);
        break;
    case IO_DIR_OUTPUT:
        *port_dir_regs[port] |= (1 << pin_bit);
        break;
    }
}

void io_set_drive(pin_e pin, io_drive_e drive)
{
    const uint8_t port = get_io_port(pin);
    const uint8_t pin_bit = get_pin_bit(pin);
    switch (drive)
    {
    case IO_LOW:
        *port_drive_regs[port] &= ~(1 << pin_bit);
        break;
    case IO_HIGH:
        *port_drive_regs[port] |= (1 << pin_bit);
        break;
    }
}

// void digitalWrite(volatile uint8_t* port, uint8_t pin, digital_write_t value)
// {
//     if (value == LOW)
//     {
//         *port &= ~(1 << pin);
//     } else {
//         *port |= (1 << pin);
//     }
// }