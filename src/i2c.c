#include "i2c.h"

#include <stdbool.h>
#include "assert_handler.h"

#define MAX_ADDR 0b01111111 // 7-bit length

static void i2c_start()
{
    // Enable TWI (aka i2c) and send start condition
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    // Wait for TWINT flag set by HW (meaning start was transmitted)
    while (!(TWCR & (1<<TWINT)))
        ;
    // Check value of TWI status register = start / repeat start
    if (TW_STATUS != TW_START && TW_STATUS != TW_REP_START)
        ASSERT(false); // error
}

static void i2c_stop()
{
    // Transmit stop
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

static void i2c_mstr_tx_addr(const uint8_t addr, const bool read_write_flag)
{
    // Assert addr within bounds
    ASSERT(addr <= MAX_ADDR);
    // Load address and start its transmission
    TWDR = (addr << 1) | read_write_flag;
    TWCR = (1<<TWINT) | (1<<TWEN);
    // Wait for TWINT flag set by HW (meaning addr was transmitted)
    while (!(TWCR & (1<<TWINT)))
        ;
    // Check value of TWI status register = MT_SLA_ASK
    if (TW_STATUS != TW_MT_SLA_ACK)
        ASSERT(false); // error
}

static void i2c_mstr_tx_data(const uint8_t data)
{
    // Load data and start its transmission
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    // Wait for data transmitted flag
    while (!(TWCR & (1<<TWINT)))
        ;
    // Check value of TWI status register = MT_DATA_ASK
    if (TW_STATUS != TW_MT_DATA_ACK)
        ASSERT(false); // error
}

static uint8_t i2c_mstr_rx_data(const bool is_last_byte)
{
    if (!is_last_byte)
    {
        // Receive data byte and send acknowledge
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
        // Wait...
        while (!(TWCR & (1 << TWINT)))
            ;
        // Check status
        if (TW_STATUS != TW_MR_DATA_ACK)
            ASSERT(false); //error
    } else {
        // Receive data byte, don't send acknowledge
        TWCR = (1 << TWINT) | (1 << TWEN);
        // Wait...
        while (!(TWCR & (1 << TWINT)))
            ;
        // Check status (= not ack)
        if (TW_STATUS != TW_MR_DATA_NACK)
            ASSERT(false); //error
    }
    // Read data
    const uint8_t data = TWDR;
    //
    return data;
}


// ====== PUBLIC METHODS

void HAL_I2C_Master_Tx(const uint8_t* data, const uint8_t len, const uint8_t slave_addr)
{
    i2c_start();
    i2c_mstr_tx_addr(slave_addr, TW_WRITE);
    // Transmit the data array byte-by-byte
    for (size_t i = 0; i < len; ++i)
    {
        i2c_mstr_tx_data(data[i]);
    }
    i2c_stop();
}

void HAL_I2C_Master_Rx(uint8_t* data, const uint8_t len, const uint8_t slave_addr)
{
    i2c_start();
    i2c_mstr_tx_addr(slave_addr, TW_READ);
    // Receive the data array byte-by-byte
    for (size_t i = 0; i < len-1; ++i)
    {
        data[i] = i2c_mstr_rx_data(false);
    }
    data[len-1] = i2c_mstr_rx_data(true);
    i2c_stop();
}