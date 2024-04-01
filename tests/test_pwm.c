#include "test_pwm.h"
#include "avr_io_mock.h"
#include "../src/gpio.h"
#include "../src/pwm.h"
#include "../src/assert_handler.h"
#include <stdbool.h>
#include <stdio.h>

void TEST_PWM_INIT(void)
{
    // Arrange
    HAL_GPIO_Init();
    // Act
    HAL_PWM_Init();
    // Assert
    ASSERT(TCCR0A == 0b00000000);
    ASSERT(TCCR0B == 0b00000000);
    ASSERT(OCR0A == 0);
    ASSERT(OCR0B == 0);
}

void TEST_PWM_CONFIGPIN(void)
{
    // Arrange
    // Act
    HAL_PWM_ConfigurePin(PIN_5, false);
    // Assert
    ASSERT(TCCR0A == 0b00100011);
    ASSERT(TCCR0B == 0b00000001);
    ASSERT(OCR0B == 0);
}

void TEST_PWM_WRITEPIN(void)
{
    // Arrange
    // Act
    HAL_PWM_Write(PIN_5, 111);
    // Assert
    ASSERT(OCR0B == 111);
}

void RUN_PWM_TESTS(void)
{
    printf("\n================ PWM TESTS ===============\n");
    TEST_PWM_INIT();
    TEST_PWM_CONFIGPIN();
    TEST_PWM_WRITEPIN();
    printf("===========================================\n");
}
