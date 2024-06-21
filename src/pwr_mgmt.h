#ifndef PWR_MGMT_H
#define PWR_MGMT_H

typedef enum
{
    MODULE_ADC,
    MODULE_USART,
    MODULE_SPI,
    MODULE_TIM1,
    MODULE_TIM0,
    MODULE_TIM2,
    MODULE_TWI,
} Module_e;

typedef enum
{
    SLEEP_MODE_IDLE             = 0b0000,
    SLEEP_MODE_ADC_NOISE_RED    = 0b0010,
    SLEEP_MODE_PWR_DOWN         = 0b0100,
    SLEEP_MODE_PWR_SAVE         = 0b0110,
    SLEEP_MODE_STANDBY          = 0b1100,
    SLEEP_MODE_EXT_STANDBY      = 0b1110,
} Power_Mode_e;

void HAL_PM_Enable_Module(Module_e module);
void HAL_PM_Disable_Module(Module_e module);
void HAL_PM_Set_Sleep_Mode(Power_Mode_e mode);
void HAL_PM_Sleep(void);
void HAL_PM_Init(void);

#endif // PWR_MGMT_H