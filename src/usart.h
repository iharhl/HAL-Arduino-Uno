#ifndef USART_H
#define USART_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    USART_MODE_ASYNC,
    USART_MODE_DASYNC,
    USART_MODE_SYNC,
    USART_MODE_SPI,
} USART_Mode_e;

typedef enum
{
    PARITY_BIT_NONE = 0b00,
    PARITY_BIT_EVEN = 0b10,
    PARITY_BIT_ODD = 0b11,
} USART_ParityBit_e;

typedef struct {
    // TODO: data bits
    USART_ParityBit_e parity_bit_format;
    bool stop_bits_2; // false -> 1, true -> 2
} USART_FrameFormat_s;

void HAL_USART_Init(const USART_FrameFormat_s* format);
void HAL_USART_Transmit(uint8_t data);
uint8_t HAL_USART_Receive(void);
void HAL_USART_SetMode(USART_Mode_e mode);

#endif //USART_H
