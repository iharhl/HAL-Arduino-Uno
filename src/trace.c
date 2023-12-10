#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include "assert_handler.h"

static bool initialized = false;

void HAL_Trace_Init(void)
{
    ASSERT(!initialized);
    // TODO: init uart
    initialized = true;
}

void trace(const char *format, ...)
{
    ASSERT(initialized);
    va_list args;
    va_start(args, format);
    printf(format, args); // change for target
    va_end(args);
}