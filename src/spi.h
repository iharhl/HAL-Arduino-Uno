#ifndef SPI_H_
#define SPI_H_

#ifdef AVR_TEST
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
void HAL_SPI_MasterTx(const char Data);
void HAL_SPI_SlaveInit(void);
char HAL_SPI_SlaveRx(void);

#endif //SPI_H_
