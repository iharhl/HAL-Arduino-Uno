#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "types.h"
#include "pwm.h"

int main(void)
{
    // Configure pin 6 (PD6) as output
    // configurePin(9, OUTPUT);
    // configurePin(10, OUTPUT);
    // configurePin(3, OUTPUT);
    HAL_GPIO_Init();
    HAL_GPIO_ConfigurePin((GPIO_Config){GPIO_DIR_OUTPUT, GPIO_PULL_DOWN}, 13);

    // PWM_init(3);

    while(1)
    {
        // PWM_send(3, 50);
        HAL_GPIO_WritePin(13, GPIO_STATE_LOW);
        _delay_ms(500);
        // PWM_send(3, 200);
        HAL_GPIO_WritePin(13, GPIO_STATE_HIGH);
        _delay_ms(500);
    }
}
