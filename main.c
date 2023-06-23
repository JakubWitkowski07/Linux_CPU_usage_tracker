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
#include "watchdog.h"


void term(int signum);


volatile sig_atomic_t done = 0;


int main(void)
{
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
    get_core_num();

    pthread_create(&reader_id, NULL, get_proc_stat_thread, NULL);
    pthread_create(&analyzer_id, NULL, calculate_usage_thread, NULL);
    pthread_create(&printer_id, NULL, printer_thread, NULL);
    pthread_create(&watchdog_id, NULL, watchdog_thread, NULL);
    
    pthread_join(reader_id, NULL);
    pthread_join(analyzer_id, NULL);
    pthread_join(printer_id, NULL);
    pthread_join(watchdog_id, NULL);
    
    return 0;
}

void term(int signum)
{
    done = 1;
}
