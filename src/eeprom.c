#include "eeprom.h"
#include "assert_handler.h"
#include "config.h"

#ifdef DEBUG_SIM
#include "../tests/avr_io_mock.h"
#else
#include <avr/io.h>
#include <avr/eeprom.h>
#endif

// TODO: disable interrupts

void HAL_EEPROM_Write_Byte(int address, const uint8_t value)
{
    /* Check if the prev value is not the same */
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