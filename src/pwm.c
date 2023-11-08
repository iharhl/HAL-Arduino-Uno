#include "pwm.h"
#include <avr/io.h>

void initPWM(void)
{
    // Set duty cycle to 0
    OCR0A = 0;

    // Set up registers
    TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00); // non-Inverting fast PWM mode 3 using OCR A unit
	TCCR0B |= (1<<CS00); // no-Prescalar
}

void sendPWM(float duty_cycle)
{
    OCR0A = (uint8_t)(255*duty_cycle); // convert 0-1 duty cycle range to register value
}