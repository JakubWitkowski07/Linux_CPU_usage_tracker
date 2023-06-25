#include "global.h"
#include "analyzer.h"
#include "watchdog.h"


void calculate_usage(struct ring_buffer *calcCurStats)
{
    for(int switchPos = 0; switchPos < BUFFER_SIZE; switchPos++)
    {
        unsigned long long int idle_prev = (calcCurStats->buffer[switchPos].stats.idle) + (calcCurStats->buffer[switchPos].stats.iowait);
        unsigned long long int idle_cur = (calcCurStats->buffer[switchPos].stats.cur_idle) + (calcCurStats->buffer[switchPos].stats.cur_iowait);

        unsigned long long int nidle_prev = (calcCurStats->buffer[switchPos].stats.user) 
                        + (calcCurStats->buffer[switchPos].stats.nice) 
                        + (calcCurStats->buffer[switchPos].stats.system) 
                        + (calcCurStats->buffer[switchPos].stats.irq) 
                        + (calcCurStats->buffer[switchPos].stats.softirq) 
                        + (calcCurStats->buffer[switchPos].stats.steal) 
                        + (calcCurStats->buffer[switchPos].stats.guest) 
                        + (calcCurStats->buffer[switchPos].stats.guest_nice);
        unsigned long long int nidle_cur = (calcCurStats->buffer[switchPos].stats.cur_user) 
                        + (calcCurStats->buffer[switchPos].stats.cur_nice) 
                        + (calcCurStats->buffer[switchPos].stats.cur_system) 
                        + (calcCurStats->buffer[switchPos].stats.cur_irq) 
                        + (calcCurStats->buffer[switchPos].stats.cur_softirq) 
                        + (calcCurStats->buffer[switchPos].stats.cur_steal) 
                        + (calcCurStats->buffer[switchPos].stats.cur_guest) 
                        + (calcCurStats->buffer[switchPos].stats.cur_guest_nice);

        unsigned long long int total_prev = idle_prev + nidle_prev;
        unsigned long long int total_cur = idle_cur + nidle_cur;

        double totald = (double) total_cur - (double) total_prev;
        double idled = (double) idle_cur - (double) idle_prev;

        double cpu_perc = (1000 * (totald - idled) / totald + 1) / 10;
        calcCurStats->buffer[switchPos].usage = cpu_perc;
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
        ring_buffer.tail = (ring_buffer.tail + 1) % BUFFER_SIZE;
        ring_buffer.count++;
        pthread_cond_signal(&ring_buffer.empty);
        pthread_mutex_unlock(&ring_buffer.mutex); 
    }
    pthread_exit(NULL);
}
