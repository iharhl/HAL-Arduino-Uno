#include "spi.h"

void HAL_SPI_MasterInit(void)
{
    // TODO: assert pin config
    /* Clear the SPI data register */
    SPDR = 0;
    /* Enable SPI and set it to Master */
    SPCR |= (1<<SPE) | (1<<MSTR);
}

void HAL_SPI_MasterTx(const char Data)
{
    // TODO: assert pin config
    /* Start transmission */
    SPDR = Data;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)))
        ;
}

void HAL_SPI_SlaveInit(void)
{
    // TODO: assert pin config
    /* Enable SPI */
    SPCR |= (1<<SPE);
    /* Reset Master bit in case it was enabled before */
    SPCR &= ~(1<<MSTR);
}

uint8_t HAL_SPI_SlaveRx(void)
{
    /* Wait for reception complete */
    while(!(SPSR & (1<<SPIF)))
        ;
    /* Return Data Register */
    return SPDR;
}