#include "global.h"
#include "watchdog.h"

time_t current_time = 0;
time_t last_activity_time = 0;


void *watchdog_thread()
{   
    current_time = time(NULL);
    last_activity_time = time(NULL);
    while (1) {
        current_time = time(NULL);
        if (current_time - last_activity_time > TIMEOUT) {
            printf("Program terminated: threads are not responding.\n");
            pthread_join(reader_id, NULL);
            pthread_join(analyzer_id, NULL);
            pthread_join(printer_id, NULL);
            pthread_join(watchdog_id, NULL);
            exit(1); // Terminate the program
        }
        sleep(2);
    }
    return NULL;
}