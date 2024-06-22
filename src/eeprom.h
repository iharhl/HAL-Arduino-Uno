#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>

void HAL_EEPROM_Write_Byte(int address, uint8_t value);
uint8_t HAL_EEPROM_Read_Byte(int address);

#endif //EEPROM_H
