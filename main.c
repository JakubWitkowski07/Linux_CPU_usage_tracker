#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "global.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"

volatile sig_atomic_t done = 0;

void term(int signum)
{
    done = 1;
}

int main(void)
{
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
    get_core_num();

    struct cpuStats statsPrev[coreNum + 1];
    struct cpuStats statsCur[coreNum + 1];
    double cpuUsage[coreNum + 1];

    while(!done)
    {
        get_proc_stats(&statsPrev);

        sleep(1);

        get_proc_stats(&statsCur);

        calculate_usage(&statsPrev, &statsCur, cpuUsage);

        print_usage(cpuUsage);

    }
    
    return 0;
}
