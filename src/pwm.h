#ifndef PWM_H_
#define PWM_H_

#include <stdbool.h>
#ifdef AVR_TEST
#include "../tests/avr_io_mock.h"
#else
#include <avr/io.h>
#endif

void HAL_PWM_Init(void); // resets all PWM registers
void HAL_PWM_Write(uint8_t Pin, uint8_t DutyCycle); // set PWM value (add more inputs?)
void HAL_PWM_Write16(uint8_t Pin, uint16_t DutyCycle);
void HAL_PWM_ConfigurePin(const uint8_t Pin, const bool PWM16);
// int16_t HAL_PWM_ReadPin(uint8_t Pin);

#endif