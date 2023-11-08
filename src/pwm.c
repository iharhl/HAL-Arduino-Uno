#include "pwm.h"
#include <avr/io.h>

/* 8-bit version */
void sendPWM(float duty_cycle)
{
    OCR0A = (uint8_t)(255*duty_cycle); // convert 0-1 duty cycle range to register value 
    TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00); // Non-Inverting Fast PWM mode 3 using OCR A unit
	TCCR0B |= (1<<CS00); // No-Prescalar
}