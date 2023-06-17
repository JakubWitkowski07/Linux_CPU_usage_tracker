#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "analyzer.h"

void calculate_usage(struct cpuStats *prev, struct cpuStats *cur, double usageArr[])
{
    for(int i = 0; i <= coreNum; i++)
    {
        double idle_prev = (prev[i].idle) + (prev[i].iowait);
        double idle_cur = (cur[i].idle) + (cur[i].iowait);

        double nidle_prev = (prev[i].user) + (prev[i].nice) + (prev[i].system) + (prev[i].irq) + (prev[i].softirq) + (prev[i].steal) + (prev[i].guest) + (prev[i].guest_nice);
        double nidle_cur = (cur[i].user) + (cur[i].nice) + (cur[i].system) + (cur[i].irq) + (cur[i].softirq) + (cur[i].steal) + (cur[i].guest) + (cur[i].guest_nice);

        double total_prev = idle_prev + nidle_prev;
        double total_cur = idle_cur + nidle_cur;

        double totald = (double) total_cur - (double) total_prev;
        double idled = (double) idle_cur - (double) idle_prev;

        usageArr[i] = (1000 * (totald - idled) / totald + 1) / 10;
    }
}
