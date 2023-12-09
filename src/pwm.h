#ifndef _PWM_H
#define _PWM_H

#ifdef AVR_TEST
#include "../tests/avr_io_mock.h"
#else
#include <avr/io.h>
#endif

/* 8-bit fast PWM */
void PWM_send(uint8_t pin, uint8_t duty_cycle);

/* 16-bit fast PWM */
void PWM_16bit_send(uint8_t pin, uint16_t duty_cycle);

/* Initialization of 8-bit PWM */
void PWM_init(uint8_t pin);

/* Initialization of 16-bit PWM */
void PWM_16bit_init(uint8_t pin);

#endif