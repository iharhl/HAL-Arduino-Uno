#include "avr_io_mock.h"
#include "assert.h"
#include "../src/usart.h"
#include "../src/config.h"

void TEST_USART_INIT(void)
{
    // Arrange
    uint32_t baud_rate = 9600;
    uint32_t ubrr = F_CPU / (baud_rate * 16) - 1;
    USART_FrameFormat_s format = { PARITY_BIT_NONE, false };
    // Act
    HAL_USART_Init(&format, baud_rate);
    // Assert
    ASSERT_EQ(UCSR0B, 0b00011000);
    ASSERT_EQ(UCSR0C, 0b00000110);
    ASSERT_EQ(UBRR0, ubrr);
}

void TEST_USART_TXBYTE(void)
{
    // Arrange
    uint8_t data = 250;
    UCSR0A = 0b00100000; // mock empty transmit buffer
    // Act
    HAL_USART_TxByte(data);
    // Assert
    ASSERT_EQ(UDR0, 250);
}

void TEST_USART_RXBYTE(void)
{
    // Arrange
    UDR0 = 125;
    UCSR0A = 0b10000000; // mock data received flag
    // Act
    uint8_t data = HAL_USART_RxByte();
    // Assert
    ASSERT_EQ(data, 125);
}

void TEST_USART_TXWORD(void)
{
    // TODO: fix approach, not fully testable
}

void TEST_USART_RXWORD(void)
{
    // Arrange
    UDR0 = 0x1A;
    UCSR0A = 0b10000000; // mock data received flag
    // Act
    uint16_t data = HAL_USART_RxWord();
    // Assert
    ASSERT_EQ(data, 0x1A1A);
}

void TEST_USART_SETMODE(void)
{
    // Arrange
    UCSR0C = 0;
    UCSR0A = 0;
    // Act
    HAL_USART_SetMode(USART_MODE_ASYNC);
    // Assert
    ASSERT_EQ(UCSR0C, 0);
    ASSERT_EQ(UCSR0A, 0);
    // Act
    HAL_USART_SetMode(USART_MODE_DASYNC);
    // Assert
    ASSERT_EQ(UCSR0C, 0);
    ASSERT_EQ(UCSR0A, 0b00000010);
    // Act
    HAL_USART_SetMode(USART_MODE_SYNC);
    // Assert
    ASSERT_EQ(UCSR0C, 0b01000000);
    ASSERT_EQ(UCSR0A, 0);
}

void RUN_USART_TESTS(void)
{
    printf("\n=============== USART TESTS =================\n");
    TEST_USART_INIT();
    TEST_USART_TXBYTE();
    TEST_USART_RXBYTE();
    TEST_USART_TXWORD();
    TEST_USART_RXWORD();
    TEST_USART_SETMODE();
    printf("===========================================\n");
}