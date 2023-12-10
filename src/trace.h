#ifndef _TRACE_H_
#define _TRACE_H_

// For now only for tests
#define TRACE(fmt, ...) trace("%s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

void HAL_Trace_Init(void);
void trace(const char* format, ...);

#endif