#include "gpio.h"

/* ============== PRIVATE METHODS ================== */

/* Get a port number based on pin number */
static inline uint8_t get_io_port(GPIO_Pin_e pin)
{
    if (pin >= 0 && pin < 8)
        return 0; // DDRD or PORTD
    else if (pin >= 8 && pin < 14)
        return 1; // DDRB or PORTB
    else if (pin >= 14 && pin < 20)
        return 2; //DDRC or PORTC
}

// TODO: fix to not repeat above
static inline uint8_t get_pin_bit(GPIO_Pin_e pin)
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
static volatile uint8_t* const port_pull_regs[PORT_NUM] = { &PORTD, &PORTB, &PORTC }; // data register

static inline void io_set_direction(GPIO_Pin_e pin, GPIO_Dir_e direction)
{
    const uint8_t port = get_io_port(pin);
    const uint8_t pin_bit = get_pin_bit(pin);
    switch (direction)
    {
    case GPIO_DIR_INPUT:
        *port_dir_regs[port] &= ~(1 << pin_bit);
        break;
    case GPIO_DIR_OUTPUT:
        *port_dir_regs[port] |= (1 << pin_bit);
        break;
    }
}

static inline void io_set_pull(GPIO_Pin_e pin, GPIO_Pull_e pull)
{
    const uint8_t port = get_io_port(pin);
    const uint8_t pin_bit = get_pin_bit(pin);
    switch (pull)
    {
    case GPIO_PULL_DOWN:
        *port_pull_regs[port] &= ~(1 << pin_bit);
        break;
    case GPIO_PULL_UP:
        *port_pull_regs[port] |= (1 << pin_bit);
        break;
    }
}

static inline void io_toggle_pin(GPIO_Pin_e pin)
{
    const uint8_t port = get_io_port(pin);
    const uint8_t pin_bit = get_pin_bit(pin);
    *port_pull_regs[port] ^= (1 << pin_bit);
}

/* ============== PUBLIC METHODS ================== */

void HAL_GPIO_ConfigurePin(GPIO_Config Config, uint8_t Pin)
{
    io_set_direction(Pin, Config.dir);
    io_set_pull(Pin, Config.pull);
}

void HAL_GPIO_WritePin(uint8_t Pin, GPIO_State_e State)
{
    // TODO: Assert pin config as output

    // Set output by re-using pull method
    io_set_pull(Pin, State);
}

void HAL_GPIO_TogglePin(uint8_t Pin)
{
    // TODO: Assert pin config as output

    io_toggle_pin(Pin);
}