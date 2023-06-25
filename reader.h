#include <stdio.h>
#include <stdint.h>
#include <pthread.h>


void get_proc_stats(struct ring_buffer *curStats);
void *get_proc_stat_thread(void* arg);
