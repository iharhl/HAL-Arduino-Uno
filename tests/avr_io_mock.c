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
extern volatile uint8_t REFS1 = 7;
extern volatile uint8_t REFS0 = 6;
extern volatile uint8_t MUX3 = 3;
extern volatile uint8_t MUX2 = 2;
extern volatile uint8_t MUX1 = 1;
extern volatile uint8_t MUX0 = 0;

// Bits No. of ADCSRA
extern volatile uint8_t ADEN = 7;
extern volatile uint8_t ADSC = 6;
extern volatile uint8_t ADIF = 4;
extern volatile uint8_t ADPS2 = 2;
extern volatile uint8_t ADPS1 = 1;
extern volatile uint8_t ADPS0 = 0;