#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/sysinfo.h>
#include <time.h>

#include "logger.h"

extern int coreNum;
extern int shouldExit;
void get_core_num(void) __attribute__((constructor));
void closing_handler(int typeOfClose) __attribute__((noreturn));
void sigint_handler(int signal);
void set_signal_action(void);
void sleep_ms(int milliseconds);

#define CORENUM sysconf(_SC_NPROCESSORS_ONLN)
#define BUFFER_SIZE 5

typedef struct cpuStats
{
    char name[7];
    unsigned long long int  user;
    unsigned long long int  nice;
    unsigned long long int  system;
    unsigned long long int  idle;
    unsigned long long int  iowait;
    unsigned long long int  irq;
    unsigned long long int  softirq;
    unsigned long long int  steal;
    unsigned long long int  guest;
    unsigned long long int  guest_nice; 

    char cur_name[7];
    unsigned long long int  cur_user;
    unsigned long long int  cur_nice;
    unsigned long long int  cur_system;
    unsigned long long int  cur_idle;
    unsigned long long int  cur_iowait;
    unsigned long long int  cur_irq;
    unsigned long long int  cur_softirq;
    unsigned long long int  cur_steal;
    unsigned long long int  cur_guest;
    unsigned long long int  cur_guest_nice;

} cpuStats_t;

typedef struct buffer_element
{
    cpuStats_t stats;
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

extern pthread_t reader_id, analyzer_id, printer_id, watchdog_id;

#endif
