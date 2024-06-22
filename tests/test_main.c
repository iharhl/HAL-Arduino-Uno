#include "test_gpio.h"
#include "test_pwm.h"
#include "test_spi.h"
#include "test_adc.h"
#include "test_power.h"
#include "test_eeprom.h"
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

    return 0;
}