#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/sysinfo.h>

#include "global.h"

int coreNum = 0;

int get_core_num()
{
    coreNum = get_nprocs();
    double cpuUsage[coreNum + 1];
    return coreNum;
}