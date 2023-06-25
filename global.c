#include "global.h"
#include <unistd.h>
#include <pthread.h>


int coreNum;

int shouldExit = 0;


ring_buffer_t ring_buffer = {
    .buffer = {{{{0}}}},
    .head = 0,
    .tail = 0,
    .count = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .empty = PTHREAD_COND_INITIALIZER,
    .full = PTHREAD_COND_INITIALIZER,
};

pthread_t reader_id, analyzer_id, printer_id, watchdog_id;


void closing_handler(int typeOfClose)
{
    if(typeOfClose == 0)
    {
        log_message(INFO, "App closed");
        exit(0);
    }
    else
    {
        log_message(INFO, "App closed because of ERROR");
        exit(1);
    }
}

void sigint_handler(int signal)
{
	if (signal == SIGINT || signal == SIGTERM)
    {
		log_message(DEBUG, "SIGINT or SIGTERM signal catched");
        shouldExit = 1;
        closing_handler(0);
    }
}

void set_signal_action(void)
{
	struct sigaction action;
	bzero(&action, sizeof(action));
	action.sa_handler = &sigint_handler;
	sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
}

void get_core_num()
{
    int bufferSize;
    coreNum = get_nprocs();
    bufferSize = coreNum + 1;
    return;
}