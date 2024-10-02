#include "unit_tests.h"
#include "../src/trace.h"

int main()
{
    HAL_Trace_Init();

    RUN_GPIO_TESTS();
    RUN_PWM_TESTS();
    RUN_SPI_TESTS();
    RUN_ADC_TESTS();
    RUN_PWR_TESTS();
    RUN_EEPROM_TESTS();
    RUN_USART_TESTS();
    RUN_I2C_TESTS();

    return 0;
}