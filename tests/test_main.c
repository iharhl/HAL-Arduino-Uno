#include "test_gpio.h"
#include "test_pwm.h"

int main()
{
    RUN_GPIO_TESTS();
    RUN_PWM_TESTS();
    return 0;
}