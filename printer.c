#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "printer.h"

void print_usage(double usage[])
{
    for(int cpuNum = 0; cpuNum <= coreNum; cpuNum++)
        {
            if(cpuNum == 0)
            {
                printf("Total CPU usage: %.2lf%% ", usage[cpuNum]);
            }
            else
            {
                printf("Core[%d] usage: %.2lf%% ", cpuNum, usage[cpuNum]);
            }
        }
        printf("\n");
}