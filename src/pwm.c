#include "pwm.h"
#include <stdbool.h>
// #include <assert.h>
#include "assert_handler.h"

static struct
{
    bool pin_3;
    bool pin_5;
    bool pin_6;
    bool pin_9;
    bool pin_10;
    bool pin_11;
} pwm_enabled;

static struct
{
    bool pin_9;
    bool pin_10;
} pwm_16bit_enabled;


void PWM_init(uint8_t pin)
{
    switch(pin)
    {
    case 3:
        ASSERT(!pwm_enabled.pin_3);
        OCR2B = 0;
        TCCR2A |= (1<<COM2B1) | (1<<WGM21) | (1<<WGM20); // non-Inverting fast PWM mode 3
        TCCR2B |= (1<<CS20); // no prescalar
        pwm_enabled.pin_3 = true;
        break;
    case 5:
        // assert(!pwm_enabled.pin_5);
        OCR0B = 0;
        TCCR0A |= (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);
        TCCR0B |= (1<<CS00);
        pwm_enabled.pin_5 = true;
        break;
    case 6:
        // assert(!pwm_enabled.pin_6);
        OCR0A = 0;
        TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
        TCCR0B |= (1<<CS00);
        pwm_enabled.pin_6 = true;
        break;
    case 9:
        /* 8-bit fast PWM - mode 5 */
        // assert(!pwm_enabled.pin_9 && !pwm_16bit_enabled.pin_9);
        OCR1A = 0;
        TCCR1A |= (1<<COM1A1) | (1<<WGM10);
        TCCR1B |= (1<<WGM12) | (1<<CS10);
        pwm_enabled.pin_9 = true;
        break;
    case 10:
        /* 8-bit fast PWM - mode 5 */
        // assert(!pwm_enabled.pin_10 && !pwm_16bit_enabled.pin_10);
        OCR1B = 0;
        TCCR1A |= (1<<COM1B1) | (1<<WGM10);
        TCCR1B |= (1<<WGM12) | (1<<CS10);
        pwm_enabled.pin_10 = true;
        break;
    case 11:
        // assert(!pwm_enabled.pin11);
        OCR2A = 0;
        TCCR2A |= (1<<COM2A1) | (1<<WGM21) | (1<<WGM20);
        TCCR2B |= (1<<CS20);
        pwm_enabled.pin_11 = true;
        break;
    }
}

/* Only supported for pins 9 and 10 */
void PWM_16bit_init(uint8_t pin)
{
    switch(pin)
    {
    case 9:
        /* 16-bit fast PWM - mode 14 */
        // assert(!pwm_enabled.pin_9 && !pwm_16bit_enabled.pin_9);
        OCR1A = 0;
        ICR1 = 640;
        TCCR1A |= (1<<COM1A1) | (1<<WGM11);
        TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS10);
        pwm_16bit_enabled.pin_9 = true;
        break;
    case 10:
        /* 16-bit fast PWM - mode 14 */
        // assert(!pwm_enabled.pin_10 && !pwm_16bit_enabled.pin_10);
        OCR1B = 0;
        ICR1 = 640;
        TCCR1A |= (1<<COM1B1) | (1<<WGM11);
        TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS10);
        pwm_16bit_enabled.pin_9 = true;
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

void PWM_16bit_send(uint8_t pin, uint16_t duty_cycle)
{
    switch(pin)
    {
    case 9:
        // assert(!pwm_enabled.pin_9 && pwm_16bit_enabled.pin_9);
        OCR1A = duty_cycle;
        break;
    case 10:
        // assert(!pwm_enabled.pin_10 && pwm_16bit_enabled.pin_10);
        OCR1B = duty_cycle;
        break;
    }
}