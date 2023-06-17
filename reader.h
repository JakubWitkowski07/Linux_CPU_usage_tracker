#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "global.h"

void get_proc_stats(struct cpuStats *stats);

#endif /*READER_H*/