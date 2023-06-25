#include "global.h"
#include "watchdog.h"
#include "logger.h"

time_t current_time = 0;
time_t last_activity_time = 0;


void *watchdog_thread(void* arg)
{   
    (void)arg;
    current_time = time(NULL);
    last_activity_time = time(NULL);
    while (!shouldExit) {
        current_time = time(NULL);
        if (current_time - last_activity_time > TIMEOUT) {
            log_message(ERROR, "Program terminated: threads are not responding");
            printf("Program terminated: threads are not responding.\n");
            closing_handler(1);
        }
        sleep(2);
    }
    pthread_exit(NULL);
}
