#ifndef _CONFIG_IO_H
#define _CONFIG_IO_H

#include <avr/io.h>
#include "types.h"

void configurePin(volatile uint8_t* data_direction_register, uint8_t pin, IO_config_t setting);
void digitalWrite(volatile uint8_t* port, uint8_t pin, digital_write_t value);

#endif