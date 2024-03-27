#include "pwm.h"
#include "assert_handler.h"
#include "gpio.h"

// TODO: add function that checks that PWM freq > 5

/* OCR1A/TCCR1A and OCR1B/TCCR1B 16-bit pwm registers
 * are not used for now
 */
#define PWM_REG_NUM 6

/* Stores which pwm pins are initialized
 */
static bool pwm_enabled[PWM_REG_NUM] = {false};

bool is_pwm16() {
    // TODO: both pin 9 and 10 use ICR1, fix needed
    return ICR1 == 0;
}


// =================================================


void HAL_PWM_Write(const uint8_t Pin, const uint8_t DutyCycle)
{
    switch(Pin)
    {
    case 3:
        ASSERT(pwm_enabled[0]);
        OCR2B = DutyCycle; // 0 till 255
        break;
    case 5:
        ASSERT(pwm_enabled[1]);
        OCR0B = DutyCycle; // 0 till 255
        break;
    case 6:
        ASSERT(pwm_enabled[2]);
        OCR0A = DutyCycle; // 0 till 255
        break;
    case 9:
        ASSERT(pwm_enabled[3]);
        OCR1A = DutyCycle; // 0 till 255
        break;
    case 10:
        ASSERT(pwm_enabled[4]);
        OCR1B = DutyCycle; // 0 till 255
        break;
    case 11:
        ASSERT(pwm_enabled[5]);
        OCR2A = DutyCycle; // 0 till 255
        break;
    default:
        ASSERT(false);
    }
}

void HAL_PWM_Write16(const uint8_t Pin, const uint16_t DutyCycle)
{
    switch(Pin)
    {
    case 9:
        ASSERT(pwm_enabled[3] && is_pwm16());
        OCR1A = DutyCycle;
        break;
    case 10:
        ASSERT(pwm_enabled[4] && is_pwm16());
        OCR1B = DutyCycle;
        break;
    default:
        ASSERT(false);
    }
}

void HAL_PWM_Init(void)
{
    // Clean output compare registers (duty cycle)
    OCR0A = 0;
    OCR0B = 0;
    OCR1A = 0;
    OCR1B = 0;
    OCR2A = 0;
    OCR2B = 0;
    // Clean timer/counter control registers (pwm mode)
    TCCR0A = 0;
    TCCR0B = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR2A = 0;
    TCCR2B = 0;
    // Clean ICR1 -> for 16-bit implementation
    ICR1 = 0;
    // Reset the pwm pins status
    for (uint8_t i = 0; i < PWM_REG_NUM; i++) {
        pwm_enabled[i] = false;
    }
}

void HAL_PWM_ConfigurePin(const uint8_t Pin, const bool PWM16)
{
    switch(Pin)
    {
        case 3:
            ASSERT(!pwm_enabled[0]);
            OCR2B = 0;
            TCCR2A |= (1<<COM2B1) | (1<<WGM21) | (1<<WGM20); // non-Inverting fast PWM mode 3
            TCCR2B |= (1<<CS20); // no prescalar
            pwm_enabled[0] = true;
            break;
        case 5:
            ASSERT(!pwm_enabled[1]);
            OCR0B = 0;
            TCCR0A |= (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);
            TCCR0B |= (1<<CS00);
            pwm_enabled[1] = true;
            break;
        case 6:
            ASSERT(!pwm_enabled[2]);
            OCR0A = 0;
            TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
            TCCR0B |= (1<<CS00);
            pwm_enabled[2] = true;
            break;
        case 9:
            ASSERT(!pwm_enabled[3]);
            if (PWM16) {
                /* 16-bit fast PWM - mode 14 */
                OCR1A = 0;
                ICR1 = 640;
                TCCR1A |= (1<<COM1A1) | (1<<WGM11);
                TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS10);
            } else {
                /* 8-bit fast PWM - mode 5 */
                OCR1A = 0;
                TCCR1A |= (1<<COM1A1) | (1<<WGM10);
                TCCR1B |= (1<<WGM12) | (1<<CS10);
            }
            pwm_enabled[3] = true;
            break;
        case 10:
            ASSERT(!pwm_enabled[4]);
            if (PWM16)
            {
                /* 16-bit fast PWM - mode 14 */
                OCR1B = 0;
                ICR1 = 640;
                TCCR1A |= (1<<COM1B1) | (1<<WGM11);
                TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS10);
            } else {
                /* 8-bit fast PWM - mode 5 */
                OCR1B = 0;
                TCCR1A |= (1<<COM1B1) | (1<<WGM10);
                TCCR1B |= (1<<WGM12) | (1<<CS10);
            }
            pwm_enabled[4] = true;
            break;
        case 11:
            ASSERT(!pwm_enabled[5]);
            OCR2A = 0;
            TCCR2A |= (1<<COM2A1) | (1<<WGM21) | (1<<WGM20);
            TCCR2B |= (1<<CS20);
            pwm_enabled[5] = true;
            break;
        default:
            ASSERT(false);
    }
}