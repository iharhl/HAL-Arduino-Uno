#include "avr_sleep_mock.h"
#include "avr_io_mock.h"

void sleep_enable(void) { SMCR |= (1<<SE); }
void sei(void) {}
void sleep_cpu(void) {}
void sleep_disable(void) { SMCR &= ~(1<<SE); }