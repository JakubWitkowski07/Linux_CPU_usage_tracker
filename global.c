#include "global.h"
#include <unistd.h>


int coreNum;

void get_core_num()
{
    int bufferSize;
    coreNum = get_nprocs();
    bufferSize = coreNum + 1;
    return;
}



ring_buffer_t ring_buffer = {
    .buffer = {0},
    .head = 0,
    .tail = 0,
    .count = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .empty = PTHREAD_COND_INITIALIZER,
    .full = PTHREAD_COND_INITIALIZER,
};