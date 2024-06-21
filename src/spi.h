#ifndef SPI_H_
#define SPI_H_

#include "config.h"
#ifdef DEBUG_SIM
#include "../tests/avr_io_mock.h"
#else
#include <avr/io.h>
#endif

/* PINOUT */
// SS   - PIN_10
// MOSI - PIN_11
// MISO - PIN_12
// SCK  - PIN_13

void HAL_SPI_MasterInit(void);
void HAL_SPI_MasterTx(const uint8_t Data);
void HAL_SPI_SlaveInit(void);
uint8_t HAL_SPI_SlaveRx(void);

#endif //SPI_H_
