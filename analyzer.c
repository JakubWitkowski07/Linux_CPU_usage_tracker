#include "global.h"
#include "analyzer.h"
#include "watchdog.h"


void calculate_usage(struct ring_buffer *calcCurStats)
{   
    while(ring_buffer.tail <=coreNum)
    {
        unsigned long long int idle_prev = (calcCurStats->buffer[ring_buffer.tail].stats.idle) + (calcCurStats->buffer[ring_buffer.tail].stats.iowait);
        unsigned long long int idle_cur = (calcCurStats->buffer[ring_buffer.tail].stats.cur_idle) + (calcCurStats->buffer[ring_buffer.tail].stats.cur_iowait);

        unsigned long long int nidle_prev = (calcCurStats->buffer[ring_buffer.tail].stats.user) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.nice) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.system) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.irq) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.softirq) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.steal) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.guest) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.guest_nice);
        unsigned long long int nidle_cur = (calcCurStats->buffer[ring_buffer.tail].stats.cur_user) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.cur_nice) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.cur_system) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.cur_irq) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.cur_softirq) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.cur_steal) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.cur_guest) 
                        + (calcCurStats->buffer[ring_buffer.tail].stats.cur_guest_nice);

        unsigned long long int total_prev = idle_prev + nidle_prev;
        unsigned long long int total_cur = idle_cur + nidle_cur;

        double totald = (double) total_cur - (double) total_prev;
        double idled = (double) idle_cur - (double) idle_prev;

        double cpu_perc = (1000 * (totald - idled) / totald + 1) / 10;
        calcCurStats->buffer[ring_buffer.tail].usage = cpu_perc;
        ring_buffer.tail++;
    }
}

void *calculate_usage_thread(void* arg) {
    (void)arg;
    while(!shouldExit) {
        last_activity_time = time(NULL);
        pthread_mutex_lock(&ring_buffer.mutex);
        while (ring_buffer.count == 0 || ring_buffer.count == 2) 
            pthread_cond_wait(&ring_buffer.full, &ring_buffer.mutex);
        calculate_usage(&ring_buffer);
        ring_buffer.count++;
        pthread_cond_signal(&ring_buffer.empty);
        pthread_mutex_unlock(&ring_buffer.mutex); 
    }
    pthread_exit(NULL);
}
