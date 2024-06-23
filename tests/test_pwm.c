#include "unit_tests.h"
#include "avr_io_mock.h"
#include "assert.h"
#include "../src/gpio.h"
#include "../src/pwm.h"
#include <stdbool.h>
#include <stdio.h>

void TEST_PWM_INIT(void)
{
    // Arrange
    HAL_GPIO_Init();
    // Act
    HAL_PWM_Init();
    // Assert
    ASSERT_EQ(TCCR0A, 0b00000000);
    ASSERT_EQ(TCCR0B, 0b00000000);
    ASSERT_EQ(OCR0A, 0);
    ASSERT_EQ(OCR0B, 0);
}

void TEST_PWM_CONFIGPIN(void)
{
    // Arrange
    // Act
    HAL_PWM_ConfigurePin(PIN_5, false);
    // Assert
    ASSERT_EQ(TCCR0A, 0b00100011);
    ASSERT_EQ(TCCR0B, 0b00000001);
    ASSERT_EQ(OCR0B, 0);
}

void TEST_PWM_WRITEPIN(void)
{
    // Arrange
    // Act
    HAL_PWM_Write(PIN_5, 111);
    // Assert
    ASSERT_EQ(OCR0B, 111);
}

void RUN_PWM_TESTS(void)
{
    printf("\n================ PWM TESTS ===============\n");
    TEST_PWM_INIT();
    TEST_PWM_CONFIGPIN();
    TEST_PWM_WRITEPIN();
    printf("===========================================\n");
}
