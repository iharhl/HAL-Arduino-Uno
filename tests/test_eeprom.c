#include "test_eeprom.h"
#include "avr_io_mock.h"
#include "../src/eeprom.h"
#include "../src/assert_handler.h"

void TEST_EEPROM_READBYTE(void)
{
    // Arrange
    int address = 9;
    EEDR = 255; // mock eeprom value stored
    EECR &= ~(1<<EEPE); // mock hardware clearing EEPE bit
                        // after prev eeprom write
    // Act
    uint8_t value = HAL_EEPROM_Read_Byte(address);
    // Assert
    ASSERT(EEAR == 0b0000001001);
    ASSERT(EECR == 0b00000001);
    ASSERT(value = 255);
    // Cleanup
    EECR = EEAR = EEDR = 0;
}

void TEST_EEPROM_WRITEBYTE(void)
{
    // Arrange
    int address = 1020;
    uint8_t value = 255;
    EECR &= ~(1<<EEPE); // mock hardware clearing EEPE bit
                        // after prev eeprom write
    // Act
    HAL_EEPROM_Write_Byte(address, value);
    EECR &= ~(1<<EERE); // mock hardware clearing EERE bit after
                        // eeprom read
    // Assert
    ASSERT(EEAR == 0b1111111100);
    ASSERT(EEDR == 0b11111111);
    ASSERT(EECR == 0b00000110);
    // Cleanup
    EECR = EEAR = EEDR = 0;
}

void RUN_EEPROM_TESTS(void)
{
    TEST_EEPROM_WRITEBYTE();
    TEST_EEPROM_READBYTE();
}
