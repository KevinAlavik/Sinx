#ifndef __LOGGER_H__
#define __LOGGER_H__


enum LogLevel {
    OK,
    WARNING,
    ERROR,
    FATAL,
    DEBUG,
    INFO
};

void log(enum LogLevel, char* tag, char* fmt, ...);

#endif // __LOGGER_H__
