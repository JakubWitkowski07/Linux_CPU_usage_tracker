#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>

#define TIMEOUT 2

extern time_t current_time;
extern time_t last_activity_time;

void *watchdog_thread();

#endif