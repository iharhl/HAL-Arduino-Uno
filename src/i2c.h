#ifndef I2C_H
#define I2C_H

#include "config.h"
#ifdef DEBUG_SIM
#include "../tests/avr_io_mock.h"
#include "../tests/avr_misc_defines.h"
#else
#include <avr/io.h>
#include <util/twi.h>
#endif

void HAL_I2C_Master_Tx(const uint8_t* data, uint8_t len, uint8_t slave_addr);
void HAL_I2C_Master_Rx(uint8_t* data, uint8_t len, uint8_t slave_addr);

#endif //I2C_H
