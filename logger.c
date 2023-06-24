#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "logger.h"

FILE* log_file;


void open_log_file()
{
    log_file = fopen("log.txt", "a");
    if(log_file == NULL)
    {
        printf("Failed to open log file\n");
        exit(1);
    }
}

void close_log_file()
{
    fclose(log_file);
}

void log_message(LogLevel level, const char* message)
{
    open_log_file();
    time_t currentTime = time(NULL);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&currentTime));

    char log_line[256];
    snprintf(log_line, sizeof(log_line), "[%s] [%s] %s\n", timestamp, level == DEBUG ? "DEBUG" : level == INFO ? "INFO" : level == WARNING ? "WARNING" : "ERROR", message);

    fprintf(log_file, "%s", log_line);

    close_log_file();
}