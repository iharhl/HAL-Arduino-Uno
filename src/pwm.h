#ifndef _PWM_H
#define _PWM_H

#include <avr/io.h>

/* 8-bit fast PWM */
void PWM_send(uint8_t pin, uint8_t duty_cycle);

/* 16-bit fast PWM */
void PWM_16bit_send(uint8_t pin, uint16_t duty_cycle);

/* Initialization of 8-bit PWM */
void PWM_init(uint8_t pin);

/* Initialization of 16-bit PWM */
void PWM_16bit_init(uint8_t pin);

#endif