#include "avr_io_mock.h"
#include "unit_tests.h"
#include "assert.h"
#include "avr_misc_defines.h"
#include "../src/i2c.h"

void TEST_I2C_MSTRTX()
{
    // Arrange
    const uint8_t data[3] = {0x50, 0x50, 0x50};
    const uint8_t slave_addr = 0x05;
    // Act
    HAL_I2C_Master_Tx(data, 3, slave_addr);
    // Assert
    ASSERT_EQ(data[2], TWDR); // can only check the last byte
}

void TEST_I2C_MSTRRX()
{
    // Arrange
    uint8_t data[3];
    const uint8_t slave_addr = 0x15;
    TWDR = 0x11; // pretend slave sent 0x11
    // Act
    HAL_I2C_Master_Rx(data, 3, slave_addr);
    // Assert
    ASSERT_EQ(data[0], TWDR);
    ASSERT_EQ(data[1], TWDR);
    ASSERT_EQ(data[2], TWDR);
}

void RUN_I2C_TESTS(void)
{
    printf("\n=============== I2C TESTS =================\n");
    TEST_I2C_MSTRTX();
    TEST_I2C_MSTRRX();
    printf("===========================================\n");
}