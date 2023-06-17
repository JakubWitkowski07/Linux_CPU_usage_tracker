#pragma once
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

extern int coreNum;

extern double cpuUsage[];

struct cpuStats
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
};

int get_core_num();