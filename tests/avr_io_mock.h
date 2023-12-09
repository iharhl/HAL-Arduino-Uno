#ifndef _AVR_IO_MOCK_
#define _AVR_IO_MOCK_

#include <stdint.h>

/* ******* Registers ********** */

// Data direction registers
extern volatile uint8_t DDRD;
extern volatile uint8_t DDRC;
extern volatile uint8_t DDRB;

// Data registers
extern volatile uint8_t PORTD;
extern volatile uint8_t PORTC;
extern volatile uint8_t PORTB;

// Output compare registers
extern volatile uint8_t OCR0A;
extern volatile uint8_t OCR0B;
extern volatile uint8_t OCR1A; // can be 16-bit?
extern volatile uint8_t OCR1B; // can be 16-bit?
extern volatile uint8_t OCR2A;
extern volatile uint8_t OCR2B;

// Timer/Counter Control Registers
extern volatile uint8_t TCCR0A;
extern volatile uint8_t TCCR0B;
extern volatile uint8_t TCCR1A;
extern volatile uint8_t TCCR1B;
extern volatile uint8_t TCCR2A;
extern volatile uint8_t TCCR2B;

// Input Capture Register (16-bit) 
extern volatile uint16_t ICR1;

/* ****** Registers' bits ********** */

// Bits No. of TCCR0A register
extern volatile uint8_t COM0A1;
extern volatile uint8_t COM0A0;
extern volatile uint8_t COM0B1;
extern volatile uint8_t COM0B0;
extern volatile uint8_t WGM01;
extern volatile uint8_t WGM00;

// Bits No. of TCCR0B register
extern volatile uint8_t WGM02;
extern volatile uint8_t CS02;
extern volatile uint8_t CS01;
extern volatile uint8_t CS00;

// Bits No. of TCCR1A register
extern volatile uint8_t COM1A1;
extern volatile uint8_t COM1A0;
extern volatile uint8_t COM1B1;
extern volatile uint8_t COM1B0;
extern volatile uint8_t WGM11;
extern volatile uint8_t WGM10;

// Bits No. of TCCR1B register
extern volatile uint8_t ICNC1;
extern volatile uint8_t ICES1;
extern volatile uint8_t WGM13;
extern volatile uint8_t WGM12;
extern volatile uint8_t CS12;
extern volatile uint8_t CS11;
extern volatile uint8_t CS10;

// Bits No. of TCCR2A register
extern volatile uint8_t COM2A1;
extern volatile uint8_t COM2A0;
extern volatile uint8_t COM2B1;
extern volatile uint8_t COM2B0;
extern volatile uint8_t WGM21;
extern volatile uint8_t WGM20;

// Bits No. of TCCR2B register
extern volatile uint8_t WGM22;
extern volatile uint8_t CS22;
extern volatile uint8_t CS21;
extern volatile uint8_t CS20;


#endif