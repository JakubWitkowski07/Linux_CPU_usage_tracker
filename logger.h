#ifndef LOGGER_H
#define LOGGER_H

typedef enum{
    DEBUG,
    INFO,
    WARNING,
    ERROR
} LogLevel;


void open_log_file();

void close_log_file();

void log_message(LogLevel level, const char* message);

#endif