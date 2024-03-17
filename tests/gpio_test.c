#include "avr_io_mock.h"
#include "../src/gpio.h"
#include "../src/assert_handler.h"
#include <stdbool.h>
#include "../src/trace.h"
#include <stdio.h>

int main()
{
    // Arrange
    printf("Arrange\n");

    // Act
    HAL_Trace_Init();
    HAL_GPIO_Init();
    printf("Act\n");

    // Assert
    ASSERT(DDRD == 0b00000000);
    ASSERT(PORTD == 0b11111111);
    printf("Assert\n");

    //
    HAL_GPIO_ConfigurePin( (GPIO_Config){GPIO_DIR_INPUT, GPIO_PULL_DOWN}, PIN_5 );
    PORTD |= (1 << PIN_5); // set to high

    //
    bool state = (bool) HAL_GPIO_ReadPin(PIN_5);

    //
    ASSERT(state == true);

    return 0;
}