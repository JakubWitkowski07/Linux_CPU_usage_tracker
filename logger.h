#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

typedef enum{
    DEBUG,
    INFO,
    WARNING,
    ERROR
} LogLevel;

extern FILE* log_file;

void open_log_file(void);

void close_log_file(void);

void log_message(LogLevel level, const char* message);

#endif
