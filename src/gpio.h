#ifndef GPIO_H_
#define GPIO_H_

#include "config.h"
#ifdef DEBUG_SIM
#include "../tests/avr_io_mock.h"
#else
#include <avr/io.h>
#endif

#define PORT_NUM 3

typedef enum
{
    PIN_0, PIN_1, PIN_2, PIN_3, PIN_4,
    PIN_5, PIN_6, PIN_7, PIN_8, PIN_9,
    PIN_10, PIN_11, PIN_12, PIN_13, PIN_14,
    PIN_A0, PIN_A1, PIN_A2, PIN_A3, PIN_A4,
    PIN_A5,
} GPIO_Pin_e;

typedef enum
{
    GPIO_DIR_INPUT,
    GPIO_DIR_OUTPUT,
} GPIO_Dir_e;

typedef enum
{
    GPIO_PULL_DOWN,
    GPIO_PULL_UP,
} GPIO_Pull_e;

typedef enum
{
    GPIO_STATE_LOW,
    GPIO_STATE_HIGH,
} GPIO_State_e;

typedef struct
{
    GPIO_Dir_e dir;
    GPIO_Pull_e pull;
} GPIO_Config;

void HAL_GPIO_Init(void);
void HAL_GPIO_ConfigurePin(GPIO_Config Config, uint8_t Pin);
void HAL_GPIO_WritePin(uint8_t Pin, GPIO_State_e State);
void HAL_GPIO_TogglePin(uint8_t Pin);
GPIO_State_e HAL_GPIO_ReadPin(uint8_t Pin);

#endif