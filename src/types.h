#ifndef __TYPES_H__
#define __TYPES_H__

typedef enum
{
    LOW,
    HIGH
} digital_write_t;

typedef enum
{
    A0 = 14,
    A1 = 15,
    A2 = 16,
    A3 = 17,
    A4 = 18,
    A5 = 19
} analog_pin_t;

#endif