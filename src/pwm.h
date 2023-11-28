#ifndef _PWM_H
#define _PWM_H

#include <avr/io.h>

/* 8-bit fast PWM */
void PWM_send(uint8_t pin, uint8_t duty_cycle);

/* Initialization of PWM */
void PWM_init(uint8_t pin);

#endif