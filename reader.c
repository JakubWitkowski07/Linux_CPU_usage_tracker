#include "global.h"
#include "reader.h"
#include "watchdog.h"
#include "logger.h"



void get_proc_stats(struct ring_buffer *curStats)
{
    char cpuStatsBuffer[100];
    int lineskip = ring_buffer.head;
    FILE *fp;
    
#ifndef UNIT_TESTS
    fp = fopen("/proc/stat", "r");
#endif
#ifdef UNIT_TESTS
    fp = fopen("test_proc_stat_prev.txt", "r");
#endif

    if(fp == NULL)
    {
        log_message(ERROR, "Failed to open /proc/stat");
    }
    while(ring_buffer.head <= coreNum)
    {
        if(ring_buffer.head > 0)
        {
        for(int core = lineskip; core > 0; core--)
        {
            fgets(cpuStatsBuffer, sizeof(cpuStatsBuffer), fp);
        }
        }

        fscanf(fp, "%s  %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu", 
                &(curStats->buffer[ring_buffer.head].stats.name[0]),
                &(curStats->buffer[ring_buffer.head].stats.user), 
                &(curStats->buffer[ring_buffer.head].stats.nice), 
                &(curStats->buffer[ring_buffer.head].stats.system), 
                &(curStats->buffer[ring_buffer.head].stats.idle), 
                &(curStats->buffer[ring_buffer.head].stats.iowait), 
                &(curStats->buffer[ring_buffer.head].stats.irq),
                &(curStats->buffer[ring_buffer.head].stats.softirq), 
                &(curStats->buffer[ring_buffer.head].stats.steal), 
                &(curStats->buffer[ring_buffer.head].stats.guest), 
                &(curStats->buffer[ring_buffer.head].stats.guest_nice));
        
        ring_buffer.head++;
    }
    fclose(fp);
    ring_buffer.head = 0;

    sleep_ms(500);

#ifndef UNIT_TESTS
    fp = fopen("/proc/stat", "r");
#endif
#ifdef UNIT_TESTS
    fp = fopen("test_proc_stat_cur.txt", "r");
#endif
    while(ring_buffer.head <= coreNum)
    {
        if(ring_buffer.head > 0)
        {
        for(int core = lineskip; core > 0; core--)
        {
            fgets(cpuStatsBuffer, sizeof(cpuStatsBuffer), fp);
        }
        }

        fscanf(fp, "%s %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu", 
                &(curStats->buffer[ring_buffer.head].stats.cur_name[0]),
                &(curStats->buffer[ring_buffer.head].stats.cur_user), 
                &(curStats->buffer[ring_buffer.head].stats.cur_nice), 
                &(curStats->buffer[ring_buffer.head].stats.cur_system), 
                &(curStats->buffer[ring_buffer.head].stats.cur_idle), 
                &(curStats->buffer[ring_buffer.head].stats.cur_iowait), 
                &(curStats->buffer[ring_buffer.head].stats.cur_irq),
                &(curStats->buffer[ring_buffer.head].stats.cur_softirq), 
                &(curStats->buffer[ring_buffer.head].stats.cur_steal), 
                &(curStats->buffer[ring_buffer.head].stats.cur_guest), 
                &(curStats->buffer[ring_buffer.head].stats.cur_guest_nice));

        ring_buffer.head++;
    }
    fclose(fp);
}

void *get_proc_stat_thread(void* arg) {
    (void)arg;
    while(!shouldExit) {
        last_activity_time = time(NULL);
        pthread_mutex_lock(&ring_buffer.mutex);
        while (ring_buffer.count == 1 || ring_buffer.count == 2) 
            pthread_cond_wait(&ring_buffer.empty, &ring_buffer.mutex);
        get_proc_stats(&ring_buffer);
        ring_buffer.count++;
        pthread_cond_signal(&ring_buffer.full);
        pthread_mutex_unlock(&ring_buffer.mutex);
    }
    pthread_exit(NULL);
}
