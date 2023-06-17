#ifndef ANALYZER_H
#define ANALYZER_H
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "global.h"

void calculate_usage(struct cpuStats *prev, struct cpuStats *cur, double usageArr[]);

#endif /*ANALYZER_H*/
