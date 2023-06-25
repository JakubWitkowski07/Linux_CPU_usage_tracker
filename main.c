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
#include "logger.h"




int main(void)
{
    set_signal_action();
    open_log_file();
    log_message(INFO, "App started");

    get_core_num();
    

    if(pthread_create(&reader_id, NULL, get_proc_stat_thread, NULL) != 0)
    {
        log_message(ERROR, "Failed to create reader thread");
    }
    else
    {
        log_message(DEBUG, "Reader thread created succesfuly");
    }

    if(pthread_create(&analyzer_id, NULL, calculate_usage_thread, NULL) != 0)
    {
        log_message(ERROR, "Failed to create analyzer thread");
    }
    else
    {
        log_message(DEBUG, "Analyzer thread created succesfuly");
    }
    
    if(pthread_create(&printer_id, NULL, printer_thread, NULL) != 0)
    {
        log_message(ERROR, "Failed to create printer thread");
    }
    else
    {
        log_message(DEBUG, "Printer thread created succesfuly");
    }
    
    if(pthread_create(&watchdog_id, NULL, watchdog_thread, NULL) != 0)
    {
        log_message(ERROR, "Failed to create reader thread");
    }
    else
    {
        log_message(DEBUG, "Watchdog thread created succesfuly");
    }

    pthread_join(reader_id, NULL);
    pthread_join(analyzer_id, NULL);
    pthread_join(printer_id, NULL);
    pthread_join(watchdog_id, NULL);

    pthread_mutex_destroy(&ring_buffer.mutex);
    pthread_cond_destroy(&ring_buffer.empty);
    pthread_cond_destroy(&ring_buffer.full);

    close_log_file();
    
    return 0;
}

