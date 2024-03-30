#ifndef ADC_H_
#define ADC_H_

#include "gpio.h"
#ifdef AVR_TEST
#include "../tests/avr_io_mock.h"
#else
#include <avr/io.h>
#endif

typedef enum
{
    INT,
    EXT_AREF,
    EXT_AVCC,
} ADC_Ref_e;

void HAL_ADC_Init(void);
void HAL_ADC_SelectVoltageRef(ADC_Ref_e VRef);
int HAL_ADC_ReadPin(GPIO_Pin_e Pin);

#endif //ADC_H_