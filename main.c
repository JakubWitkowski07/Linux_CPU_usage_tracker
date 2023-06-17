#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "global.h"
#include "reader.h"

int main(void)
{
    get_core_num();
    printf("%d\n", coreNum);

    struct cpuStats statsPrev[coreNum + 1];
    struct cpuStats statsCur[coreNum + 1];

    get_proc_stats(&statsPrev);
    
    return 0;
}