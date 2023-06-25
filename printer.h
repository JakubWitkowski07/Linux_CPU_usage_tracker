#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include "global.h"

void print_usage(struct ring_buffer *results);
void *printer_thread(void* arg);
