#include "pwm.h"
#include <stdbool.h>
#include <assert.h>

static struct
{
    bool pin3;
    bool pin5;
    bool pin6;
    bool pin9;
    bool pin10;
    bool pin11;
} pwm_enabled;

void PWM_init(uint8_t pin)
{
    switch(pin)
    {
    case 3:
        // assert(!pwm_enabled.pin3);
        OCR2B = 0;
        TCCR2A |= (1<<COM2B1) | (1<<WGM21) | (1<<WGM20); // non-Inverting fast PWM mode 3
        TCCR2B |= (1<<CS20); // no prescalar
        pwm_enabled.pin3 = true;
        break;
    case 5:
        // assert(!pwm_enabled.pin5);
        OCR0B = 0;
        TCCR0A |= (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);
        TCCR0B |= (1<<CS00);
        pwm_enabled.pin5 = true;
        break;
    case 6:
        // assert(!pwm_enabled.pin6);
        OCR0A = 0;
        TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
        TCCR0B |= (1<<CS00);
        pwm_enabled.pin6 = true;
        break;
    case 9:
        // assert(!pwm_enabled.pin9);
        OCR1A = 0;
        TCCR0A |= (1<<COM1A1) | (1<<WGM11) | (1<<WGM10);
        TCCR0B |= (1<<CS10);
        pwm_enabled.pin9 = true;
        break;
    case 10:
        // assert(!pwm_enabled.pin10);
        OCR1B = 0;
        TCCR0A |= (1<<COM1B1) | (1<<WGM11) | (1<<WGM10);
        TCCR0B |= (1<<CS10);
        pwm_enabled.pin10 = true;
        break;
    case 11:
        // assert(!pwm_enabled.pin11);
        OCR2A = 0;
        TCCR2A |= (1<<COM2A1) | (1<<WGM21) | (1<<WGM20);
        TCCR2B |= (1<<CS20);
        pwm_enabled.pin11 = true;
        break;
    }
}

void PWM_send(uint8_t pin, uint8_t duty_cycle)
{
    switch(pin)
    {
    case 3:
        // assert(pwm_enabled.pin3);
        OCR2B = duty_cycle; // 0 till 255
        break;
    case 5:
        // assert(pwm_enabled.pin5);
        OCR0B = duty_cycle; // 0 till 255
        break;
    case 6:
        // assert(pwm_enabled.pin6);
        OCR0A = duty_cycle; // 0 till 255
        break;
    case 9:
        // assert(pwm_enabled.pin9);
        OCR1A = duty_cycle; // 0 till 255
        break;
    case 10:
        // assert(pwm_enabled.pin10);
        OCR1B = duty_cycle; // 0 till 255
        break;
    case 11:
        // assert(pwm_enabled.pin11);
        OCR2A = duty_cycle; // 0 till 255
        break;
    }
}
