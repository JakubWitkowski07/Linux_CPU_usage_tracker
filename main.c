#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "global.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"

int main(void)
{
    get_core_num();

    struct cpuStats statsPrev[coreNum + 1];
    struct cpuStats statsCur[coreNum + 1];
    double cpuUsage[coreNum + 1];

    while(1)
    {
        get_proc_stats(&statsPrev);

        sleep(1);

        get_proc_stats(&statsCur);

        calculate_usage(&statsPrev, &statsCur, cpuUsage);

        print_usage(cpuUsage);
    }
    
    return 0;
}
