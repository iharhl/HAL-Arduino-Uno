#include "avr_io_mock.h"
#include "unit_tests.h"
#include "assert.h"
#include "../src/power.h"

void TEST_PWR_INIT(void)
{
    // Arrange
    // Act
    HAL_PWR_Init();
    // Assert
    ASSERT_EQ(SMCR, 0);
    ASSERT_EQ(MCUCR, 0);
    ASSERT_EQ(PRR, 0);
}

void TEST_PWR_SLEEP() // TODO: improve
{
    // Arrange
    // Act
    HAL_PWR_Sleep();
    // Assert
    ASSERT_EQ(SMCR, 0);
}

void TEST_PWR_SETSLEEPMODE()
{
    // Arrange
    // Act
    HAL_PWR_Set_Sleep_Mode(SLEEP_MODE_ADC_NOISE_RED);
    // Assert
    ASSERT_EQ(SMCR, 0b0010);
    // Act
    HAL_PWR_Set_Sleep_Mode(SLEEP_MODE_STANDBY);
    // Assert
    ASSERT_EQ(SMCR, 0b1100);
    // Act
    HAL_PWR_Set_Sleep_Mode(SLEEP_MODE_IDLE);
    // Assert
    ASSERT_EQ(SMCR, 0b0000);
}

void TEST_PWR_DISABLEMODULE()
{
    // Arrange
    // Act
    HAL_PWR_Disable_Module(MODULE_USART);
    // Assert
    ASSERT_EQ(PRR, 0b00000010);
    // Act
    HAL_PWR_Disable_Module(MODULE_TIM1);
    // Assert
    ASSERT_EQ(PRR, 0b00001010);
    // Act
    HAL_PWR_Disable_Module(MODULE_TWI);
    // Assert
    ASSERT_EQ(PRR, 0b10001010);
    // Act
    HAL_PWR_Disable_Module(MODULE_TWI);
    // Assert
    ASSERT_EQ(PRR, 0b10001010);
}

void TEST_PWR_ENABLEMODULE()
{
    // Arrange
    // Act
    HAL_PWR_Enable_Module(MODULE_USART);
    // Assert
    ASSERT_EQ(PRR, 0b10001000);
    // Act
    HAL_PWR_Enable_Module(MODULE_TIM1);
    // Assert
    ASSERT_EQ(PRR, 0b10000000);
    // Act
    HAL_PWR_Enable_Module(MODULE_TWI);
    // Assert
    ASSERT_EQ(PRR, 0b00000000);
    // Act
    HAL_PWR_Enable_Module(MODULE_TWI);
    // Assert
    ASSERT_EQ(PRR, 0b00000000);
}

void RUN_PWR_TESTS(void)
{
    printf("\n=============== PWR TESTS =================\n");
    TEST_PWR_INIT();
    TEST_PWR_SETSLEEPMODE();
    TEST_PWR_DISABLEMODULE();
    TEST_PWR_ENABLEMODULE();
    printf("===========================================\n");
}