#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>


extern int coreNum;
void get_core_num() __attribute__((constructor));

#define CORENUM sysconf(_SC_NPROCESSORS_ONLN)
#define BUFFER_SIZE 5

typedef struct cpuStats
{
    char name[7];
    uint32_t user;
    uint32_t nice;
    uint32_t system;
    uint32_t idle;
    uint32_t iowait;
    uint32_t irq;
    uint32_t softirq;
    uint32_t steal;
    uint32_t guest;
    uint32_t guest_nice; 

    char cur_name[7];
    uint32_t cur_user;
    uint32_t cur_nice;
    uint32_t cur_system;
    uint32_t cur_idle;
    uint32_t cur_iowait;
    uint32_t cur_irq;
    uint32_t cur_softirq;
    uint32_t cur_steal;
    uint32_t cur_guest;
    uint32_t cur_guest_nice;

};

typedef struct buffer_element
{
    struct cpuStats stats;
    double usage;
} buffer_element_t;

typedef struct ring_buffer {
    buffer_element_t buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t empty;
    pthread_cond_t full;
} ring_buffer_t;

extern ring_buffer_t ring_buffer;


#endif