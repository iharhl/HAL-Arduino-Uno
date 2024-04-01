#include "test_gpio.h"
#include "avr_io_mock.h"
#include "../src/gpio.h"
#include "../src/assert_handler.h"
#include <stdbool.h>
#include <stdio.h>

void TEST_GPIO_INIT(void)
{
    // Arrange
    // Act
    HAL_GPIO_Init();
    // Assert
    ASSERT(DDRD == 0b00000000); // port dir INPUT
    ASSERT(PORTD == 0b11111111); // port pull UP
}

void TEST_GPIO_CONFIGPIN(void)
{
    // Arrange
    HAL_GPIO_ConfigurePin( (GPIO_Config){GPIO_DIR_OUTPUT, GPIO_PULL_DOWN}, PIN_0 );
    // Act
    // Assert
    ASSERT(DDRD == 0b00000001); // port dir OUTPUT
    ASSERT(PORTD == 0b11111110); // port pull DOWN
}

void TEST_GPIO_READPIN(void)
{
    // Arrange
    HAL_GPIO_ConfigurePin( (GPIO_Config){GPIO_DIR_INPUT, GPIO_PULL_DOWN}, PIN_1 );
    PORTD |= (1 << PIN_1); // mock input to high
    // Act
    bool state = (bool) HAL_GPIO_ReadPin(PIN_1);
    // Assert
    ASSERT(state == true);
}

void TEST_GPIO_WRITEPIN(void)
{
    // Arrange
    HAL_GPIO_ConfigurePin( (GPIO_Config){GPIO_DIR_OUTPUT, GPIO_PULL_DOWN}, PIN_2 );
    // Act 1
    HAL_GPIO_WritePin(PIN_2, GPIO_STATE_LOW);
    // Assert 1
    ASSERT(PORTD == 0b11111010);
    // Act 2
    HAL_GPIO_WritePin(PIN_2, GPIO_STATE_HIGH);
    // Assert 2
    ASSERT(PORTD == 0b11111110);
}

void TEST_GPIO_TOGGLEPIN(void)
{
    // Arrange
    // Act
    HAL_GPIO_TogglePin(PIN_2);
    // Assert
    ASSERT(PORTD == 0b11111010);
}

void RUN_GPIO_TESTS(void)
{
    printf("\n================= GPIO TESTS =================\n");
    TEST_GPIO_INIT();
    TEST_GPIO_CONFIGPIN();
    TEST_GPIO_READPIN();
    TEST_GPIO_WRITEPIN();
    TEST_GPIO_TOGGLEPIN();
    printf("===========================================\n");
}