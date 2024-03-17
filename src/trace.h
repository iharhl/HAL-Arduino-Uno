#ifndef TRACE_H_
#define TRACE_H_

// For now only for tests
//#define TRACE(fmt, ...) trace("%s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define TRACE(fmt, ...) fprintf(stderr, "%s:%d:%s(): " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

void HAL_Trace_Init(void);
//void trace(const char* format, ...);

#endif