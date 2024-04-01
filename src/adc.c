#include "adc.h"
#include "assert_handler.h"

void HAL_ADC_Init(void)
{
    ADMUX = (1<<REFS1) | (1<<REFS0); // internal ref
    ADMUX |= (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0); // input channel as GND
    ADCSRA = (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // prescaler clkfq/128
    ADCSRA |= (1<<ADEN); // enable ADC
}

void HAL_ADC_SelectVoltageRef(const ADC_Ref_e VRef)
{
    switch(VRef)
    {
    case INT:
        ADMUX |= (1<<REFS1) | (1<<REFS0);
        break;
    case EXT_AREF:
        ADMUX &= ~(1<<REFS1) & ~(1<<REFS0);
        break;
    case EXT_AVCC:
        ADMUX &= ~(1<<REFS1);
        ADMUX |= (1<<REFS0);
        break;
    }
}

uint16_t HAL_ADC_ReadPin(GPIO_Pin_e Pin)
{
    if (Pin < PIN_A0)
        ASSERT(0);

    // Set input channel to read
    switch(Pin)
    {
    case PIN_A0:
        ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1) & ~(1<<MUX0);
        break;
    case PIN_A1:
        ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1);
        ADMUX |= (1<<MUX0);
        break;
    case PIN_A2:
        ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX0);
        ADMUX |= (1<<MUX1);
        break;
    case PIN_A3:
        ADMUX &= ~(1<<MUX3) & ~(1<<MUX2);
        ADMUX |= (1<<MUX1) | (1<<MUX0);
        break;
    case PIN_A4:
        ADMUX &= ~(1<<MUX3) & ~(1<<MUX1) & ~(1<<MUX0);
        ADMUX |= (1<<MUX2);
        break;
    case PIN_A5:
        ADMUX &= ~(1<<MUX3) & ~(1<<MUX1);
        ADMUX |= (1<<MUX2) | (1<<MUX0);
        break;
    }

    // Start conversion
    ADCSRA |= (1<<ADSC);

    // Wait for ADC conversion complete interrupt
    while((ADCSRA & (1<<ADIF)) == 0)
        ;

    // Read low and high ADC byte
    const uint8_t adc_rx_byte_l = ADCL;
    const uint8_t adc_rx_byte_h = ADCH;

    return (uint16_t)(adc_rx_byte_l + adc_rx_byte_h * (1<<8));
}