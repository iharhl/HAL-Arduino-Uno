#include "test_pwr_mgmt.h"
#include "../src/pwr_mgmt.h"
#include "../src/assert_handler.h"
#include "avr_io_mock.h"

void TEST_PM_INIT(void)
{
    // Arrange
    // Act
    HAL_PM_Init();
    // Assert
    ASSERT(SMCR == 0);
    ASSERT(MCUCR == 0);
    ASSERT(PRR == 0);
}

void TEST_PM_SLEEP() // TODO: improve
{
    // Arrange
    // Act
    HAL_PM_Sleep();
    // Assert
    ASSERT(SMCR == 0);
}

void TEST_PM_SETSLEEPMODE()
{
    // Arrange
    // Act
    HAL_PM_Set_Sleep_Mode(SLEEP_MODE_ADC_NOISE_RED);
    // Assert
    ASSERT(SMCR == 0b0010);
    // Act
    HAL_PM_Set_Sleep_Mode(SLEEP_MODE_STANDBY);
    // Assert
    ASSERT(SMCR == 0b1100);
    // Act
    HAL_PM_Set_Sleep_Mode(SLEEP_MODE_IDLE);
    // Assert
    ASSERT(SMCR == 0b0000);
}

void RUN_PM_DISABLEMODULE()
{
    // Arrange
    // Act
    HAL_PM_Disable_Module(MODULE_USART);
    // Assert
    ASSERT(PRR == 0b00000010);
    // Act
    HAL_PM_Disable_Module(MODULE_TIM1);
    // Assert
    ASSERT(PRR == 0b00001010);
    // Act
    HAL_PM_Disable_Module(MODULE_TWI);
    // Assert
    ASSERT(PRR == 0b10001010);
    // Act
    HAL_PM_Disable_Module(MODULE_TWI);
    // Assert
    ASSERT(PRR == 0b10001010);
}

void RUN_PM_ENABLEMODULE()
{
    // Arrange
    // Act
    HAL_PM_Enable_Module(MODULE_USART);
    // Assert
    ASSERT(PRR == 0b10001000);
    // Act
    HAL_PM_Enable_Module(MODULE_TIM1);
    // Assert
    ASSERT(PRR == 0b10000000);
    // Act
    HAL_PM_Enable_Module(MODULE_TWI);
    // Assert
    ASSERT(PRR == 0b00000000);
    // Act
    HAL_PM_Enable_Module(MODULE_TWI);
    // Assert
    ASSERT(PRR == 0b00000000);
}

void RUN_PM_TESTS(void)
{
    printf("\n=============== PWR MGMT TESTS ===============\n");
    TEST_PM_INIT();
    TEST_PM_SETSLEEPMODE();
    RUN_PM_DISABLEMODULE();
    RUN_PM_ENABLEMODULE();
    printf("===========================================\n");
}