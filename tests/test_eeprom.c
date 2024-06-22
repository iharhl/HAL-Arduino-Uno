#include "unit_tests.h"
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
    ASSERT(value == 255);
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

void TEST_EEPROM_READWORD(void)
{
    // Arrange
    int address = 9;
    EEDR = 0xFA; // mock eeprom value stored (2x for this test)
    EECR &= ~(1<<EEPE); // mock hardware clearing EEPE bit
                        // after prev eeprom write
    // Act
    uint16_t value = HAL_EEPROM_Read_Word(address);
    // Assert
    ASSERT(value == 0xFAFA);
    // Cleanup
    EECR = EEAR = EEDR = 0;
}

void TEST_EEPROM_WRITEWORD(void)
{
    // TODO: not testable with current approach
    // The test is going to be locked in while loop.
}

void TEST_EEPROM_READFLOAT(void)
{
    // Arrange
    int address = 9;
    float expected_value = 3.0039215087890625; // hex = 0x40404040
    float expected_error = 0.0000000087890625;
    EEDR = 0x40; // mock eeprom value stored (4x for this test)
    EECR &= ~(1<<EEPE); // mock hardware clearing EEPE bit
                        // after prev eeprom write
    // Act
    float value = HAL_EEPROM_Read_Float(address);
    // Assert
    ASSERT(expected_value >= value - expected_error);
    ASSERT(expected_value <= value + expected_error);
    // Cleanup
    EECR = EEAR = EEDR = 0;
}

void TEST_EEPROM_WRITEFLOAT(void)
{
    // TODO: not testable with current approach
    // The test is going to be locked in while loop.
}

void RUN_EEPROM_TESTS(void)
{
    printf("\n================ EEPROM TESTS ===============\n");
    TEST_EEPROM_WRITEBYTE();
    TEST_EEPROM_READBYTE();
    TEST_EEPROM_READWORD();
    TEST_EEPROM_WRITEWORD();
    TEST_EEPROM_READFLOAT();
    TEST_EEPROM_WRITEFLOAT();
    printf("===========================================\n");
}
