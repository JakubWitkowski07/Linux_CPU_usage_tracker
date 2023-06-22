#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#include "global.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"


void term(int signum);


volatile sig_atomic_t done = 0;


int main(void)
{
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
    get_core_num();

    pthread_t reader, analyzer, printer;

    pthread_create(&reader, NULL, get_proc_stat_thread, NULL);
    pthread_create(&analyzer, NULL, calculate_usage_thread, NULL);
    pthread_create(&printer, NULL, printer_thread, NULL);

    pthread_join(reader, NULL);
    pthread_join(analyzer, NULL);
    pthread_join(printer, NULL);

    return 0;
}

void term(int signum)
{
    done = 1;
}
