#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>

void HAL_EEPROM_Write_Byte(int address, uint8_t value);
uint8_t HAL_EEPROM_Read_Byte(int address);

void HAL_EEPROM_Write_Word(int address, uint16_t value);
uint16_t HAL_EEPROM_Read_Word(int address);

void HAL_EEPROM_Write_Float(int address, float value);
float HAL_EEPROM_Read_Float(int address);

#endif //EEPROM_H
