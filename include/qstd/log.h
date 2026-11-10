#pragma once
#ifndef QSTD_LOG_H
#define QSTD_LOG_H

#include "types.h"
#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    QSTD_LOG_TRACE = 0,
    QSTD_LOG_DEBUG,
    QSTD_LOG_INFO,
    QSTD_LOG_WARN,
    QSTD_LOG_ERROR,
    QSTD_LOG_FATAL,
    QSTD_LOG_NONE
} qstd_log_level;

/* Set global log level. Messages below this level are ignored. */
void qstd_log_set_level(qstd_log_level level);
qstd_log_level qstd_log_get_level(void);

/* Core log function (printf-style) */
void qstd_log(qstd_log_level level, const char* file, int line,
              const char* fmt, ...) QSTD_PRINTF_FMT(4, 5);

/* User hook to redirect output (e.g., to file, syslog). NULL = stderr */
typedef void (*qstd_log_sink)(qstd_log_level, const char* msg, void* user);
void qstd_log_set_sink(qstd_log_sink sink, void* user);

#ifdef __cplusplus
} /* extern "C" */
#endif

/* Macros */
#define QSTD_LOG_TRACE(...) qstd_log(QSTD_LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define QSTD_LOG_DEBUG(...) qstd_log(QSTD_LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define QSTD_LOG_INFO(...)  qstd_log(QSTD_LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define QSTD_LOG_WARN(...)  qstd_log(QSTD_LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define QSTD_LOG_ERROR(...) qstd_log(QSTD_LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define QSTD_LOG_FATAL(...) qstd_log(QSTD_LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

#endif /* QSTD_LOG_H */