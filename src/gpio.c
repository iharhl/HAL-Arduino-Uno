#include "gpio.h"
#include "assert_handler.h"
#include <stdio.h> // remove

/* ============== PRIVATE METHODS ================== */

/* Get a port number based on pin number */
static inline uint8_t get_port(GPIO_Pin_e pin)
{
    if (pin >= 0 && pin < 8)
        return 0; // DDRD or PORTD
    else if (pin >= 8 && pin < 14)
        return 1; // DDRB or PORTB
    else if (pin >= 14 && pin < 21)
        return 2; //DDRC or PORTC
    else
        ASSERT(0);
}

// TODO: fix to not repeat above
static inline uint8_t get_pin_bit(GPIO_Pin_e pin)
{
    if (pin >= 0 && pin < 8)
        return pin;
    else if (pin >= 8 && pin < 14)
        return pin-8;
    else if (pin >= 14 && pin < 21)
        return pin-14;
    else
        ASSERT(0);
}

// Registers
static volatile uint8_t* const port_dir_regs[PORT_NUM] = { &DDRD, &DDRB, &DDRC }; // data direction registers
static volatile uint8_t* const port_pull_regs[PORT_NUM] = { &PORTD, &PORTB, &PORTC }; // data register


/* ============== PUBLIC METHODS ================== */


/* Default configuration:
    * Configures all pins as inputs
    * Configure pull-up resistor
*/
void HAL_GPIO_Init(void)
{
    for (int i = PIN_0; i <= PIN_A5; i++)
    {
        const uint8_t port = get_port(i);
        const uint8_t pin_bit = get_pin_bit(i);
        *port_dir_regs[port] &= ~(1 << pin_bit);
        *port_pull_regs[port] |= (1 << pin_bit);

    }
}

void HAL_GPIO_ConfigurePin(GPIO_Config Config, uint8_t Pin)
{
    const uint8_t port = get_port(Pin);
    const uint8_t pin_bit = get_pin_bit(Pin);
    
    switch (Config.dir)
    {
    case GPIO_DIR_INPUT:
        *port_dir_regs[port] &= ~(1 << pin_bit);
        break;
    case GPIO_DIR_OUTPUT:
        *port_dir_regs[port] |= (1 << pin_bit);
        break;
    }

    switch (Config.pull)
    {
    case GPIO_PULL_DOWN:
        *port_pull_regs[port] &= ~(1 << pin_bit);
        break;
    case GPIO_PULL_UP:
        *port_pull_regs[port] |= (1 << pin_bit);
        break;
    }
}

void HAL_GPIO_WritePin(uint8_t Pin, GPIO_State_e State)
{
    // TODO: Assert pin config as output

    const uint8_t port = get_port(Pin);
    const uint8_t pin_bit = get_pin_bit(Pin);

    switch (State)
    {
    case GPIO_STATE_LOW:
        *port_pull_regs[port] &= ~(1 << pin_bit);
        break;
    case GPIO_STATE_HIGH:
        *port_pull_regs[port] |= (1 << pin_bit);
        break;
    }
}

void HAL_GPIO_TogglePin(uint8_t Pin)
{
    // TODO: Assert pin config as output

    const uint8_t port = get_port(Pin);
    const uint8_t pin_bit = get_pin_bit(Pin);
    *port_pull_regs[port] ^= (1 << pin_bit); // can also do it with PINxn
}