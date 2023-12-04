#ifndef _GPIO_H_
#define _GPIO_H_

#include <avr/io.h>
#include "types.h"

#define PORT_NUM 3

// void configurePin(uint8_t pin, io_dir_e setting);
// void digitalWrite(volatile uint8_t* port, uint8_t PIN_, digital_write_t value);

typedef enum
{
    PIN_0, PIN_1, PIN_2, PIN_3, PIN_4,
    PIN_5, PIN_6, PIN_7, PIN_8, PIN_9,
    PIN_10, PIN_11, PIN_12, PIN_13, PIN_14,
} pin_e;

typedef enum
{
    IO_DIR_INPUT,
    IO_DIR_OUTPUT,
} io_dir_e;

typedef enum
{
    IO_LOW,
    IO_HIGH, // pull-up for input
} io_drive_e;

struct io_config
{
    io_dir_e dir;
    io_drive_e drive;
};

void io_set_direction(pin_e pin, io_dir_e direction);
void io_set_drive(pin_e pin, io_drive_e drive);

#endif