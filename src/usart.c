#include "usart.h"
#include "assert_handler.h"

#ifdef DEBUG_SIM
#include "../tests/avr_io_mock.h"
#else
#include <avr/io.h>
#endif

#define BAUD_PRESCALE (F_CPU / (USART_BAUD_RATE * 16UL) - 1)

// UBBRn register is 11 bits long
#define BAUD_PRESCALE_MIN 0
#define BAUD_PRESCALE_MAX 2047

void HAL_USART_Init(const USART_FrameFormat_s* format)
{
    /*Set baud rate */
    ASSERT(BAUD_PRESCALE >= BAUD_PRESCALE_MIN && BAUD_PRESCALE <= BAUD_PRESCALE_MAX);
    UBRR0 = BAUD_PRESCALE;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    /* Write the frame format */
    UCSR0C = (format->parity_bit_format << UPM01) | (format->stop_bits_2 << USBS0);
    /* Set 8-bit data */
    UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
}

void HAL_USART_Transmit(const uint8_t data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

uint8_t HAL_USART_Receive(void)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)))
        ;
    /* Get and return received data from buffer */
    return UDR0;
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
