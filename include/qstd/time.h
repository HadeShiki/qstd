#pragma once
#ifndef QSTD_TIME_H
#define QSTD_TIME_H

#include "types.h"

#ifdef _WIN32
#  include <windows.h>
#  include <ctime>
#else
#  include <time.h>
#  include <sys/time.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Milliseconds since epoch */
QSTD_INLINE qstd_i64 qstd_time_ms(void) {
#ifdef _WIN32
    FILETIME ft; GetSystemTimeAsFileTime(&ft);
    ULARGE_INTEGER ui; ui.LowPart = ft.dwLowDateTime; ui.HighPart = ft.dwHighDateTime;
    return (qstd_i64)((ui.QuadPart - 116444736000000000ULL) / 10000ULL);
#else
    struct timeval tv; gettimeofday(&tv, NULL);
    return (qstd_i64)tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif
}

/* Microseconds since epoch */
QSTD_INLINE qstd_i64 qstd_time_us(void) {
#ifdef _WIN32
    return qstd_time_ms() * 1000;
#else
    struct timeval tv; gettimeofday(&tv, NULL);
    return (qstd_i64)tv.tv_sec * 1000000 + tv.tv_usec;
#endif
}

/* High-resolution monotonic timer (for benchmarking) */
QSTD_INLINE qstd_i64 qstd_time_ns(void) {
#if defined(_WIN32)
    static LARGE_INTEGER freq = {0};
    if (freq.QuadPart == 0) QueryPerformanceFrequency(&freq);
    LARGE_INTEGER c; QueryPerformanceCounter(&c);
    return (qstd_i64)((c.QuadPart * 1000000000LL) / freq.QuadPart);
#else
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts);
    return (qstd_i64)ts.tv_sec * 1000000000LL + ts.tv_nsec;
#endif
}

/* Format current time: "YYYY-MM-DD HH:MM:SS" */
QSTD_INLINE void qstd_time_now_str(char* buf, size_t buf_size) {
    time_t t = time(NULL);
    struct tm tmv;
#ifdef _WIN32
    localtime_s(&tmv, &t);
#else
    localtime_r(&t, &tmv);
#endif
    strftime(buf, buf_size, "%Y-%m-%d %H:%M:%S", &tmv);
}

/* Sleep in milliseconds */
QSTD_INLINE void qstd_sleep_ms(unsigned ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (long)(ms % 1000) * 1000000L;
    nanosleep(&ts, NULL);
#endif
}

#ifdef __cplusplus
} /* extern "C" */

#include <chrono>
#include <string>

namespace qstd {

/* RAII scoped timer (nanoseconds) */
class Stopwatch {
public:
    Stopwatch() : _start(std::chrono::high_resolution_clock::now()) {}
    void reset() { _start = std::chrono::high_resolution_clock::now(); }
    double elapsed_ms() const {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(now - _start).count();
    }
    double elapsed_us() const { return elapsed_ms() * 1000.0; }
    double elapsed_s()  const { return elapsed_ms() / 1000.0; }
private:
    std::chrono::high_resolution_clock::time_point _start;
};

inline std::string now_str() {
    char buf[32];
    qstd_time_now_str(buf, sizeof(buf));
    return std::string(buf);
}

}
#endif

#endif /* QSTD_TIME_H */