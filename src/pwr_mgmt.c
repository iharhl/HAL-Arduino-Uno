#include "pwr_mgmt.h"

#ifdef DEBUG_SIM
#include "../tests/avr_io_mock.h"
#include "../tests/avr_sleep_mock.h"
#else
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#endif

void HAL_PM_Enable_Module(const Module_e module)
{
    switch(module)
    {
        case MODULE_ADC:
            PRR &= ~(1<<PRADC);
        break;
        case MODULE_USART:
            PRR &= ~(1<<PRUSART0);
        break;
        case MODULE_SPI:
            PRR &= ~(1<<PRSPI);
        break;
        case MODULE_TIM1:
            PRR &= ~(1<<PRTIM1);
        break;
        case MODULE_TIM0:
            PRR &= ~(1<<PRTIM0);
        break;
        case MODULE_TIM2:
            PRR &= ~(1<<PRTIM2);
        break;
        case MODULE_TWI:
            PRR &= ~(1<<PRTWI);
        break;
    }
}

void HAL_PM_Disable_Module(const Module_e module)
{
    switch(module)
    {
    case MODULE_ADC:
        PRR |= (1<<PRADC);
        break;
    case MODULE_USART:
        PRR |= (1<<PRUSART0);
        break;
    case MODULE_SPI:
        PRR |= (1<<PRSPI);
        break;
    case MODULE_TIM1:
        PRR |= (1<<PRTIM1);
        break;
    case MODULE_TIM0:
        PRR |= (1<<PRTIM0);
        break;
    case MODULE_TIM2:
        PRR |= (1<<PRTIM2);
        break;
    case MODULE_TWI:
        PRR |= (1<<PRTWI);
        break;
    }
}

void HAL_PM_Set_Sleep_Mode(const Power_Mode_e mode)
{
    SMCR = (uint8_t)mode;
}

void HAL_PM_Sleep()
{
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();
}

void HAL_PM_Init(void)
{
    SMCR = 0;
    MCUCR = 0; // TODO: implement functionality
    PRR = 0;
}