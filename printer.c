#include "global.h"
#include "printer.h"


void print_usage(struct ring_buffer *results)
{
    for(int cpuNumber = 0; cpuNumber <= coreNum; cpuNumber++)
        {
            if(cpuNumber == 0)
            {
                printf("Total CPU usage: %.2lf%% ", results->buffer[cpuNumber].usage);
            }
            else
            {
                printf("Core[%d] usage: %.2lf%% ", cpuNumber, results->buffer[cpuNumber].usage);
            }
        }     
        printf("\n");
}


void *printer_thread() {
    while(1) {
        pthread_mutex_lock(&ring_buffer.mutex);
        while (ring_buffer.count == 1) 
            pthread_cond_wait(&ring_buffer.full, &ring_buffer.mutex);
        print_usage(&ring_buffer.buffer);
        ring_buffer.count = 0;
        pthread_cond_signal(&ring_buffer.empty);
        pthread_mutex_unlock(&ring_buffer.mutex);
        sleep(1);
    }
}