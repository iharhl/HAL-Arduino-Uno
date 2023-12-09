#ifndef ASSERT_HANDLER_H_
#define ASSERT_HANDLER_H_

#ifdef AVR_TEST
#include <stdlib.h>
#define ASSERT(expression)      \
    do                          \
    {                           \
        if (!(expression))      \
        {                       \
            exit(1);            \
        }                       \
    } while(0)
#else
#define ASSERT(expression)      \
    do                          \
    {                           \
        if (!(expression))      \
        {                       \
            assert_handler();   \
        }                       \
    } while(0)
#endif

// TODO
void assert_handler(void);

#endif