#include "global.h"
#include "reader.h"
#include "watchdog.h"
#include "logger.h"



void get_proc_stats(struct ring_buffer *curStats)
{
    char cpuStatsBuffer[100];
    int lineskip = ring_buffer.head;
    FILE *fp;
    
    fp = fopen("/proc/stat", "r");
    if(fp == NULL)
    {
        log_message(ERROR, "Failed to open /proc/stat");
    }
    for(int switchPos = 0; switchPos < BUFFER_SIZE; switchPos++)
    {
        if(switchPos > 0)
        {
        for(int coreNum = lineskip; coreNum > 0; coreNum--)
        {
            fgets(cpuStatsBuffer, sizeof(cpuStatsBuffer), fp);
        }
        }

        fscanf(fp, "%s  %u %u %u %u %u %u %u %u %u %u", 
                &(curStats->buffer[switchPos].stats.name[0]),
                &(curStats->buffer[switchPos].stats.user), 
                &(curStats->buffer[switchPos].stats.nice), 
                &(curStats->buffer[switchPos].stats.system), 
                &(curStats->buffer[switchPos].stats.idle), 
                &(curStats->buffer[switchPos].stats.iowait), 
                &(curStats->buffer[switchPos].stats.irq),
                &(curStats->buffer[switchPos].stats.softirq), 
                &(curStats->buffer[switchPos].stats.steal), 
                &(curStats->buffer[switchPos].stats.guest), 
                &(curStats->buffer[switchPos].stats.guest_nice));
    }
    fclose(fp);

    usleep(100000);

    fp = fopen("/proc/stat", "r");
    for(int switchPos = 0; switchPos < BUFFER_SIZE; switchPos++)
    {
        if(switchPos > 0)
        {
        for(int coreNum = lineskip; coreNum > 0; coreNum--)
        {
            fgets(cpuStatsBuffer, sizeof(cpuStatsBuffer), fp);
        }
        }
        fscanf(fp, "%s %u %u %u %u %u %u %u %u %u %u", 
                &(curStats->buffer[switchPos].stats.cur_name[0]),
                &(curStats->buffer[switchPos].stats.cur_user), 
                &(curStats->buffer[switchPos].stats.cur_nice), 
                &(curStats->buffer[switchPos].stats.cur_system), 
                &(curStats->buffer[switchPos].stats.cur_idle), 
                &(curStats->buffer[switchPos].stats.cur_iowait), 
                &(curStats->buffer[switchPos].stats.cur_irq),
                &(curStats->buffer[switchPos].stats.cur_softirq), 
                &(curStats->buffer[switchPos].stats.cur_steal), 
                &(curStats->buffer[switchPos].stats.cur_guest), 
                &(curStats->buffer[switchPos].stats.cur_guest_nice));

        ring_buffer.head = (ring_buffer.head + 1) % BUFFER_SIZE;
    }
    fclose(fp);
}

void *get_proc_stat_thread() {
    while(1) {
        last_activity_time = time(NULL);
        pthread_mutex_lock(&ring_buffer.mutex);
        while (ring_buffer.count == 1 || ring_buffer.count == 2) 
            pthread_cond_wait(&ring_buffer.empty, &ring_buffer.mutex);
        get_proc_stats(&ring_buffer.buffer);
        ring_buffer.count++;
        pthread_cond_signal(&ring_buffer.full);
        pthread_mutex_unlock(&ring_buffer.mutex);
    }
}