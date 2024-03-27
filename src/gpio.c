#include "gpio.h"
#include "assert_handler.h"
#include <stdio.h> // remove


/* ============== PRIVATE METHODS ================== */

/* Get a port index based on a pin number */
static inline uint8_t get_port(const GPIO_Pin_e pin)
{
    if (pin < 8)
        return 0; // DDRD or PORTD
    else if (pin >= 8 && pin < 14)
        return 1; // DDRB or PORTB
    else if (pin >= 14 && pin < 21)
        return 2; //DDRC or PORTC
    ASSERT(0);
}

/* Get a pin bit index of the corresponding port
 * based on a pin number */
static inline uint8_t get_pin_bit(const GPIO_Pin_e pin)
{
    if (pin < 8)
        return (uint8_t)pin;
    else if (pin >= 8 && pin < 14)
        return (uint8_t)(pin-8);
    else if (pin >= 14 && pin < 21)
        return (uint8_t)(pin-14);
    ASSERT(0);
}

/* Registers put into an array */
static volatile uint8_t* const port_dir_regs[PORT_NUM] =
    { &DDRD, &DDRB, &DDRC }; // data direction registers
static volatile uint8_t* const port_pull_regs[PORT_NUM] =
    { &PORTD, &PORTB, &PORTC }; // data register


/* ============== PUBLIC METHODS ================== */

/* Default configuration:
    * Configures all pins as inputs
    * Configures pull-up resistor
*/
void HAL_GPIO_Init(void)
{
    for (GPIO_Pin_e i = PIN_0; i <= PIN_A5; i++)
    {
        const uint8_t port = get_port(i);
        const uint8_t pin_bit = get_pin_bit(i);
        *port_dir_regs[port] &= ~(1 << pin_bit);
        *port_pull_regs[port] |= (1 << pin_bit);
    }
}

void HAL_GPIO_ConfigurePin(const GPIO_Config Config, const uint8_t Pin)
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

void HAL_GPIO_WritePin(const uint8_t Pin, const GPIO_State_e State)
{
    // TODO: Assert pin config as output
    // e.g.: read_gpio_config()

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

void HAL_GPIO_TogglePin(const uint8_t Pin)
{
    // TODO: Assert pin config as output

    const uint8_t port = get_port(Pin);
    const uint8_t pin_bit = get_pin_bit(Pin);
    *port_pull_regs[port] ^= (1 << pin_bit); // can also do it with PINxn
}

GPIO_State_e HAL_GPIO_ReadPin(const uint8_t Pin)
{
    // TODO: Assert pin config as input

    const uint8_t port = get_port(Pin);
    const uint8_t pin_bit = get_pin_bit(Pin);

    return *port_pull_regs[port] &= (1 << pin_bit);
}