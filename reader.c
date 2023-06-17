#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "global.h"
#include "reader.h"

void get_proc_stats(struct cpuStats *stats)
{
    char cpu[7];
    FILE *fp = fopen("/proc/stat", "r");

    /* Save stats for CPU */
    for(int cpuNum = 0; cpuNum <= coreNum; cpuNum++)
    {
        fscanf(fp, "%s %u %u %u %u %u %u %u %u %u %u", 
            &(stats[cpuNum].name[0]),
            &(stats[cpuNum].user), 
            &(stats[cpuNum].nice), 
            &(stats[cpuNum].system), 
            &(stats[cpuNum].idle), 
            &(stats[cpuNum].iowait), 
            &(stats[cpuNum].irq),
            &(stats[cpuNum].softirq), 
            &(stats[cpuNum].steal), 
            &(stats[cpuNum].guest), 
            &(stats[cpuNum].guest_nice));
    }
        
    fclose(fp);
    return;
}