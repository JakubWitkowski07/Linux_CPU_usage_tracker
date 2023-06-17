#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "global.h"
#include "reader.h"
#include "analyzer.h"

int main(void)
{
    get_core_num();

    struct cpuStats statsPrev[coreNum + 1];
    struct cpuStats statsCur[coreNum + 1];

    get_proc_stats(&statsPrev);
    sleep(1);
    get_proc_stats(&statsCur);

    double cpuUsage[coreNum + 1];

    calculate_usage(&statsPrev, &statsCur, cpuUsage);
    
    return 0;
}