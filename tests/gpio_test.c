#include "avr_io_mock.h"
#include "../src/gpio.h"
#include "../src/assert_handler.h"
#include <stdio.h>

int main()
{
    // Arrange
    printf("Arrange");

    // Act
    HAL_GPIO_Init();
    printf("Act");

    // Assert
    printf((int)DDRD);
    printf((int)PORTD);
    ASSERT(DDRD == 0b00000000);
    ASSERT(PORTD == 0b11111111);

    return 0;
}