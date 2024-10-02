#include "avr_io_mock.h"

/* ******* Registers ********** */

// Data direction registers
volatile uint8_t DDRD = 0;
volatile uint8_t DDRC = 0;
volatile uint8_t DDRB = 0;

// Data registers
volatile uint8_t PORTD = 0;
volatile uint8_t PORTC = 0;
volatile uint8_t PORTB = 0;

// Output compare registers
volatile uint8_t OCR0A = 0;
volatile uint8_t OCR0B = 0;
volatile uint8_t OCR1A = 0; // can be 16-bit?
volatile uint8_t OCR1B = 0; // can be 16-bit?
volatile uint8_t OCR2A = 0;
volatile uint8_t OCR2B = 0;

// Timer/Counter Control Registers
volatile uint8_t TCCR0A = 0;
volatile uint8_t TCCR0B = 0;
volatile uint8_t TCCR1A = 0;
volatile uint8_t TCCR1B = 0;
volatile uint8_t TCCR2A = 0;
volatile uint8_t TCCR2B = 0;

// Input Capture Register (16-bit) 
volatile uint16_t ICR1 = 0;

// SPI Registers
volatile uint8_t SPCR = 0; // SPI Control Register
volatile uint8_t SPSR = 0; // SPI Status Register
volatile uint8_t SPDR = 0; // SPI Data Register

// ADC Registers
volatile uint8_t ADMUX = 0; // ADC Multiplexer Selection Register
volatile uint8_t ADCSRA = 0; // ADC Control and Status Register A
volatile uint8_t ADCL = 0; // ADC Data Register (low byte)
volatile uint8_t ADCH = 0; // ADC Data Register (high byte)

// Power Registers
volatile uint8_t SMCR = 0; // Sleep Mode Control Register
volatile uint8_t MCUCR = 0; // MCU Control Register
volatile uint8_t PRR = 0; // Power Reduction Register

// EEPROM Registers
volatile uint16_t EEAR = 0; // EEPROM Address Register
volatile uint8_t EEDR = 0; // EEPROM Data Register
volatile uint8_t EECR = 0; // EEPROM Control Register

// USART Registers
volatile uint8_t UDR0 = 0; // USART I/O Data Register
volatile uint8_t UCSR0A = 0; // USART Control and Status Register A
volatile uint8_t UCSR0B = 0; // USART Control and Status Register B
volatile uint8_t UCSR0C = 0; // USART Control and Status Register C
volatile uint16_t UBRR0 = 0; // USART Baud Rate Register (H and L)

// I2C Registers
volatile uint8_t TWBR = 0; // TWI Bit Rate Register
volatile uint8_t TWCR = 0; // TWI Control Register
volatile uint8_t TWSR = 0; // TWI Status Register
volatile uint8_t TWDR = 0; // TWI Data Register
volatile uint8_t TWAR = 0; // TWI (Slave) Address Register


/* ****** Registers' bits ********** */

// Bits No. of TCCR0A register
volatile uint8_t COM0A1 = 7;
volatile uint8_t COM0A0 = 6;
volatile uint8_t COM0B1 = 5;
volatile uint8_t COM0B0 = 4;
volatile uint8_t WGM01 = 1;
volatile uint8_t WGM00 = 0;

// Bits No. of TCCR0B register
volatile uint8_t WGM02 = 3;
volatile uint8_t CS02 = 2;
volatile uint8_t CS01 = 1;
volatile uint8_t CS00 = 0;

// Bits No. of TCCR1A register
volatile uint8_t COM1A1 = 7;
volatile uint8_t COM1A0 = 6;
volatile uint8_t COM1B1 = 5;
volatile uint8_t COM1B0 = 4;
volatile uint8_t WGM11 = 1;
volatile uint8_t WGM10 = 0;

// Bits No. of TCCR1B register
volatile uint8_t ICNC1 = 7;
volatile uint8_t ICES1 = 6;
volatile uint8_t WGM13 = 4;
volatile uint8_t WGM12 = 3;
volatile uint8_t CS12 = 2;
volatile uint8_t CS11 = 1;
volatile uint8_t CS10 = 0;

// Bits No. of TCCR2A register
volatile uint8_t COM2A1 = 7;
volatile uint8_t COM2A0 = 6;
volatile uint8_t COM2B1 = 5;
volatile uint8_t COM2B0 = 4;
volatile uint8_t WGM21 = 1;
volatile uint8_t WGM20 = 0;

// Bits No. of TCCR2B register
volatile uint8_t WGM22 = 3;
volatile uint8_t CS22 = 2;
volatile uint8_t CS21 = 1;
volatile uint8_t CS20 = 0;

// Bits No. of SPCR
volatile uint8_t SPIE = 7;
volatile uint8_t SPE = 6;
volatile uint8_t DORD = 5;
volatile uint8_t MSTR = 4;
volatile uint8_t CPOL = 3;
volatile uint8_t CPHA = 2;
volatile uint8_t SPR1 = 1;
volatile uint8_t SPR0 = 0;

// Bits No. of SPSR
volatile uint8_t SPIF = 7;
volatile uint8_t WCOL = 6;
volatile uint8_t SPI2X = 0;

// Bits No. of ADMUX
volatile uint8_t REFS1 = 7;
volatile uint8_t REFS0 = 6;
volatile uint8_t MUX3 = 3;
volatile uint8_t MUX2 = 2;
volatile uint8_t MUX1 = 1;
volatile uint8_t MUX0 = 0;

// Bits No. of ADCSRA
volatile uint8_t ADEN = 7;
volatile uint8_t ADSC = 6;
volatile uint8_t ADIF = 4;
volatile uint8_t ADPS2 = 2;
volatile uint8_t ADPS1 = 1;
volatile uint8_t ADPS0 = 0;

// Bits No. of SMCR
volatile uint8_t SE = 0;
volatile uint8_t SM0 = 1;
volatile uint8_t SM1 = 2;
volatile uint8_t SM2 = 3;

// Bits No. of PRR
volatile uint8_t PRADC = 0;
volatile uint8_t PRUSART0 = 1;
volatile uint8_t PRSPI = 2;
volatile uint8_t PRTIM1 = 3;
volatile uint8_t PRTIM0 = 5;
volatile uint8_t PRTIM2 = 6;
volatile uint8_t PRTWI = 7;

// Bits No. of EECR
volatile uint8_t EEPM1 = 5;
volatile uint8_t EEPM0 = 4;
volatile uint8_t EERIE = 3;
volatile uint8_t EEMPE = 2;
volatile uint8_t EEPE = 1;
volatile uint8_t EERE = 0;

// Bits of UCSR0A
volatile uint8_t RXC0 = 7;
volatile uint8_t TXC0 = 6;
volatile uint8_t UDRE0 = 5;
volatile uint8_t FE0 = 4;
volatile uint8_t DOR0 = 3;
volatile uint8_t UPE0 = 2;
volatile uint8_t U2X0 = 1;
volatile uint8_t MPCM0 = 0;

// Bits of UCSR0B
volatile uint8_t RXCIE0 = 7;
volatile uint8_t TXCIE0 = 6;
volatile uint8_t UDRIE0 = 5;
volatile uint8_t RXEN0 = 4;
volatile uint8_t TXEN0 = 3;
volatile uint8_t UCSZ02 = 2;
volatile uint8_t RXB80 = 1;
volatile uint8_t TXB80 = 0;

// Bits of UCSR0C
volatile uint8_t UMSEL01 = 7;
volatile uint8_t UMSEL00 = 6;
volatile uint8_t UPM01 = 5;
volatile uint8_t UPM00 = 4;
volatile uint8_t USBS0 = 3;
volatile uint8_t UCSZ01 = 2;
volatile uint8_t UCSZ00 = 1;
volatile uint8_t UCPOL0 = 0;

// Bits of TWBR
volatile uint8_t TWBR7 = 7;
volatile uint8_t TWBR6 = 6;
volatile uint8_t TWBR5 = 5;
volatile uint8_t TWBR4 = 4;
volatile uint8_t TWBR3 = 3;
volatile uint8_t TWBR2 = 2;
volatile uint8_t TWBR1 = 1;
volatile uint8_t TWBR0 = 0;

// Bits of TWCR
volatile uint8_t TWINT = 7;
volatile uint8_t TWEA = 6;
volatile uint8_t TWSTA = 5;
volatile uint8_t TWSTO = 4;
volatile uint8_t TWWC = 3;
volatile uint8_t TWEN = 2;
volatile uint8_t TWIE = 0;

// Bits of TWSR
volatile uint8_t TWS7 = 7;
volatile uint8_t TWS6 = 6;
volatile uint8_t TWS5 = 5;
volatile uint8_t TWS4 = 4;
volatile uint8_t TWS3 = 3;
volatile uint8_t TWPS1 = 1;
volatile uint8_t TWPS0 = 0;

// Bits of TWDR
volatile uint8_t TWD7 = 7;
volatile uint8_t TWD6 = 6;
volatile uint8_t TWD5 = 5;
volatile uint8_t TWD4 = 4;
volatile uint8_t TWD3 = 3;
volatile uint8_t TWD2 = 2;
volatile uint8_t TWD1 = 1;
volatile uint8_t TWD0 = 0;

// Bits of TWAR
volatile uint8_t TWA6 = 7;
volatile uint8_t TWA5 = 6;
volatile uint8_t TWA4 = 5;
volatile uint8_t TWA3 = 4;
volatile uint8_t TWA2 = 3;
volatile uint8_t TWA1 = 2;
volatile uint8_t TWA0 = 1;
volatile uint8_t TWGCE = 0;

