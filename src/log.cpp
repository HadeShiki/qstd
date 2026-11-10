#include "qstd/log.h"
#include "qstd/time.h"
#include <string.h>
#include <stdlib.h>
#include <mutex>

static qstd_log_level g_level = QSTD_LOG_INFO;
static qstd_log_sink  g_sink  = NULL;
static void*          g_user  = NULL;
static std::mutex     g_mutex;

static const char* level_name(qstd_log_level l) {
    switch (l) {
        case QSTD_LOG_TRACE: return "TRACE";
        case QSTD_LOG_DEBUG: return "DEBUG";
        case QSTD_LOG_INFO:  return "INFO ";
        case QSTD_LOG_WARN:  return "WARN ";
        case QSTD_LOG_ERROR: return "ERROR";
        case QSTD_LOG_FATAL: return "FATAL";
        default: return "?????";
    }
}

static const char* level_color(qstd_log_level l) {
    switch (l) {
        case QSTD_LOG_TRACE: return "\033[90m";
        case QSTD_LOG_DEBUG: return "\033[36m";
        case QSTD_LOG_INFO:  return "\033[32m";
        case QSTD_LOG_WARN:  return "\033[33m";
        case QSTD_LOG_ERROR: return "\033[31m";
        case QSTD_LOG_FATAL: return "\033[1;31m";
        default: return "";
    }
}

extern "C" void qstd_log_set_level(qstd_log_level level) { g_level = level; }
extern "C" qstd_log_level qstd_log_get_level(void) { return g_level; }

extern "C" void qstd_log_set_sink(qstd_log_sink sink, void* user) {
    g_sink = sink; g_user = user;
}

extern "C" void qstd_log(qstd_log_level level, const char* file, int line,
                          const char* fmt, ...) {
    if (level < g_level || level == QSTD_LOG_NONE) return;

    char msg[2048];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    if (g_sink) {
        std::lock_guard<std::mutex> lk(g_mutex);
        g_sink(level, msg, g_user);
        return;
    }

    /* Short filename */
    const char* base = file ? file : "?";
    for (const char* p = base; *p; ++p)
        if (*p == '/' || *p == '\\') base = p + 1;

    char ts[32];
    qstd_time_now_str(ts, sizeof(ts));

    std::lock_guard<std::mutex> lk(g_mutex);
    fprintf(stderr, "%s[%s] %s %s:%d: %s\033[0m\n",
            level_color(level), level_name(level), ts, base, line, msg);
}