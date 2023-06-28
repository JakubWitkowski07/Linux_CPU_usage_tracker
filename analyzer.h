#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>

void calculate_usage(struct ring_buffer *calcCurStats);
void *calculate_usage_thread(void* arg);
