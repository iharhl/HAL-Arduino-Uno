#include "eeprom.h"
#include "assert_handler.h"
#include "config.h"
#include "utils.h"

#ifdef DEBUG_SIM
#include "../tests/avr_io_mock.h"
#else
#include <avr/io.h>
#include <avr/eeprom.h>
#endif

// TODO: disable interrupts

void HAL_EEPROM_Write_Byte(int address, const uint8_t value)
{
    /* Check if the value changed */
    if (HAL_EEPROM_Read_Byte(address) == value)
        return;
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE))
        ;
    /* Set up address and Data Registers */
    EEAR = address;
    EEDR = value;
    /* Write logical one to EEMPE */
    EECR |= (1<<EEMPE);
    /* Start eeprom write by setting EEPE */
    EECR |= (1<<EEPE);
}

uint8_t HAL_EEPROM_Read_Byte(int address)
{
    /* Assert address does not overflow */
    ASSERT(address < EEPROM_SIZE);
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE))
        ;
    /* Set up address register */
    EEAR = address;
    /* Start eeprom read by writing EERE */
    EECR |= (1<<EERE);
    /* Return data from Data Register */
    return EEDR;
}

void HAL_EEPROM_Write_Word(int address, uint16_t value)
{
    /* Split value into low and high byte */
    const uint8_t eeprom_byte_l = value & 0xFF;
    const uint8_t eeprom_byte_h = (value >> 8) & 0xFF;
    /* Write bytes one-by-one */
    HAL_EEPROM_Write_Byte(address, eeprom_byte_l);
    HAL_EEPROM_Write_Byte(address+1, eeprom_byte_h);
}

uint16_t HAL_EEPROM_Read_Word(int address)
{
    /* Read low byte */
    const uint8_t eeprom_byte_l = HAL_EEPROM_Read_Byte(address);
    /* Read high byte */
    const uint8_t eeprom_byte_h = HAL_EEPROM_Read_Byte(address+1);
    /* Return combined value */
    return eeprom_byte_l + eeprom_byte_h * (1<<8);
}

void HAL_EEPROM_Write_Float(int address, float value)
{
    /* Split value into low and high word */
    const uint32_t value_dword = reinterpret_cast(uint32_t, value);
    const uint16_t eeprom_word_l = value_dword & 0xFFFF;
    const uint16_t eeprom_word_h = (value_dword >> 16) & 0xFFFF;
    /* Write words one-by-one */
    HAL_EEPROM_Write_Word(address, eeprom_word_l);
    HAL_EEPROM_Write_Word(address+2, eeprom_word_h);
}

float HAL_EEPROM_Read_Float(int address)
{
    /* Read low word */
    const uint16_t eeprom_word_l = HAL_EEPROM_Read_Word(address);
    /* Read high word */
    const uint16_t eeprom_word_h = HAL_EEPROM_Read_Word(address+2);
    /* Return combined value */
    const uint32_t eeprom_dword = eeprom_word_l + eeprom_word_h * (1<<16);
    return reinterpret_cast(float, eeprom_dword);
}