#include "avr_io_mock.h"
#include "../src/gpio.h"
#include "../src/assert_handler.h"
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

    return 0;
}