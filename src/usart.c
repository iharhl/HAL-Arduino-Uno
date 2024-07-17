#include "usart.h"
#include "assert_handler.h"

#ifdef DEBUG_SIM
#include "../tests/avr_io_mock.h"
#else
#include <avr/io.h>
#endif

#define BAUD_PRESCALE

// UBBRn register is 11 bits long
#define BAUD_PRESCALE_MAX ((1<<12)-1)

void HAL_USART_Init(const USART_FrameFormat_s* format, const uint32_t baud_rate)
{
    /* Set baud rate */
    const uint16_t ubrr = F_CPU / (baud_rate * 16) - 1;
    ASSERT(ubrr <= BAUD_PRESCALE_MAX);
    UBRR0 = ubrr;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    /* Write the frame format */
    UCSR0C = (format->parity_bit_format << UPM01) | (format->stop_bits_2 << USBS0);
    /* Set 8-bit data */
    UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
}

void HAL_USART_TxByte(const uint8_t data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

uint8_t HAL_USART_RxByte(void)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)))
        ;
    /* Get and return received data from buffer */
    return UDR0;
}

void HAL_USART_TxWord(const uint16_t data)
{
    /* Split value into low and high byte */
    const uint8_t data_byte_l = data & 0xFF;
    const uint8_t data_byte_h = (data >> 8) & 0xFF;
    /* Transmit bytes one-by-one */
    HAL_USART_TxByte(data_byte_l);
    HAL_USART_TxByte(data_byte_h);
}

uint16_t HAL_USART_RxWord(void)
{
    /* Receive bytes one-by-one */
    const uint8_t data_byte_l = HAL_USART_RxByte();
    const uint8_t data_byte_h = HAL_USART_RxByte();
    /* Return combined value */
    return data_byte_l + data_byte_h * (1<<8);
}

void HAL_USART_SetMode(const USART_Mode_e mode)
{
    switch(mode)
    {
        case USART_MODE_ASYNC:
            UCSR0C &= ~(1<<UMSEL00) & ~(1<<UMSEL01); // enable async
            UCSR0A &= ~(1<<U2X0); // disable double speed for async
            break;
        case USART_MODE_DASYNC:
            UCSR0C &= ~(1<<UMSEL00) & ~(1<<UMSEL01); // enable async
            UCSR0A |= (1<<U2X0); // enable double speed for async
            break;
        case USART_MODE_SYNC:
            UCSR0C |= (1<<UMSEL00);
            UCSR0C &= ~(1<<UMSEL01);
            UCSR0A &= ~(1<<U2X0); // disable double speed for async
            break;
        case USART_MODE_SPI:
            // Not implemented
            break;
    }
}
