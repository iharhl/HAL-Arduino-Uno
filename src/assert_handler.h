#ifndef ASSERT_HANDLER_H_
#define ASSERT_HANDLER_H_

#include <stdio.h>
#include "config.h"

#ifdef DEBUG_SIM
#include <stdlib.h>
#include "trace.h"
#define ASSERT(expression)      \
    do                          \
    {                           \
        if (!(expression))      \
            TRACE("FAILURE");   \
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
void assert_handler(void) __attribute__((noreturn));

#endif