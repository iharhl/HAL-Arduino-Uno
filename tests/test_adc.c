#include "unit_tests.h"
#include "avr_io_mock.h"
#include "../src/gpio.h"
#include "../src/adc.h"
#include "../src/assert_handler.h"
#include <stdbool.h>
#include <stdio.h>

void TEST_ADC_INIT(void)
{
    // Arrange
    HAL_GPIO_Init();
    // Act
    HAL_ADC_Init();
    // Assert
    ASSERT(ADMUX == 0b11001111);
    ASSERT(ADCSRA == 0b10000111);
}

void TEST_ADC_SELVOLTREF(void)
{
    // Arrange
    // Act
    HAL_ADC_SelectVoltageRef(EXT_AREF);
    // Assert
    ASSERT(ADMUX == 0b00001111);
}

void TEST_ADC_READPIN(void)
{
    // Arrange
    ADCL = 0b11011001; // mock low byte (=217)
    ADCH = 0b00000010; // mock high byte (=2*256)
    ADCSRA |= (1<<ADIF); // mock adc complete interrupt
    // Act
    uint16_t res = HAL_ADC_ReadPin(PIN_A0);
    ADCSRA &= ~(1<<ADSC); // mock adc conversion complete
    // Assert
    ASSERT(ADMUX == 0b00000000); // input chan select is set to ADC0
    ASSERT(res == 729);
}

void RUN_ADC_TESTS(void)
{
    printf("\n================= ADC TESTS =================\n");
    TEST_ADC_INIT();
    TEST_ADC_SELVOLTREF();
    TEST_ADC_READPIN();
    printf("===========================================\n");
}