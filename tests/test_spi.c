#include "test_spi.h"
#include "avr_io_mock.h"
#include "../src/gpio.h"
#include "../src/spi.h"
#include "../src/assert_handler.h"
#include <stdbool.h>
#include <stdio.h>

void TEST_SPI_SLAVEINIT(void)
{
    // Arrange
    HAL_GPIO_Init();
    // Act
    HAL_SPI_SlaveInit();
    //Assert
    ASSERT(SPCR == 0b01000000);
}

void TEST_SPI_SLAVERX(void)
{
    // Arrange
    SPDR = 130;
    // Act
    SPSR |= (1<<SPIF); // mock Rx flag to be set to avoid inf loop
    uint8_t res = HAL_SPI_SlaveRx();
    //Assert
    ASSERT(res == 130);
}

void TEST_SPI_MASTERINIT(void)
{
    // Arrange
    HAL_GPIO_Init();
    // Act
    HAL_SPI_MasterInit();
    //Assert
    ASSERT(SPDR == 0);
    ASSERT(SPCR == 0b01010000);
}

void TEST_SPI_MASTERTX(void)
{
    // Arrange
    // Act
    SPSR |= (1<<SPIF); // mock Tx flag to be set to avoid inf loop
    HAL_SPI_MasterTx(250);
    //Assert
    ASSERT(SPDR == 250);
}

void RUN_SPI_TESTS(void)
{
    printf("\n================ SPI TESTS ================\n");
    TEST_SPI_MASTERINIT();
    TEST_SPI_MASTERTX();
    TEST_SPI_SLAVEINIT();
    TEST_SPI_SLAVERX();
    printf("===========================================\n");
}
