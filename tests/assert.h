#ifndef ASSERT_H
#define ASSERT_H

#include "../src/trace.h"
#include <stdio.h>


#define ASSERT_EQ(val1, val2)    \
    do                           \
    {                            \
        if (val1 != val2)        \
            TRACE("FAIL");       \
        else                     \
            TRACE("PASS");       \
    } while(0)


// TODO: implement ULP approach
#define ASSERT_FLOAT_EQ(val1, val2)      \
    do                                   \
    {                                    \
        if ((val1 < val2-0.0001) ||      \
            (val1 > val2+0.0001))        \
            TRACE("FAIL");               \
        else                             \
            TRACE("PASS");               \
    } while(0)


#endif //ASSERT_H
