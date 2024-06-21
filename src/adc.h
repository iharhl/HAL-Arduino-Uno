#ifndef ADC_H_
#define ADC_H_

#include "config.h"
#include "gpio.h"
#ifdef DEBUG_SIM
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
uint16_t HAL_ADC_ReadPin(GPIO_Pin_e Pin);

#endif //ADC_H_
