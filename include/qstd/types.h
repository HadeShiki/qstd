#pragma once
#ifndef QSTD_TYPES_H
#define QSTD_TYPES_H

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
    #define _CRT_SECURE_NO_WARNINGS
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* ... ที่เหลือเหมือนเดิม ... */

/* Version */
#define QSTD_VERSION_MAJOR 1
#define QSTD_VERSION_MINOR 0
#define QSTD_VERSION_PATCH 0

/* Compiler detection */
#if defined(_MSC_VER)
    #define QSTD_COMPILER_MSVC 1
#elif defined(__clang__)
    #define QSTD_COMPILER_CLANG 1
#elif defined(__GNUC__)
    #define QSTD_COMPILER_GCC 1
#endif

/* C++ detection & inline */
#ifdef __cplusplus
    #define QSTD_CPP 1
    #define QSTD_INLINE inline
    #define QSTD_NULL nullptr
#else
    #define QSTD_CPP 0
    #define QSTD_INLINE static inline
    #define QSTD_NULL NULL
#endif

/* Attributes */
#if defined(__GNUC__) || defined(__clang__)
    #define QSTD_PRINTF_FMT(f, a) __attribute__((format(printf, f, a)))
    #define QSTD_NORETURN __attribute__((noreturn))
    #define QSTD_LIKELY(x)   __builtin_expect(!!(x), 1)
    #define QSTD_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define QSTD_PRINTF_FMT(f, a)
    #define QSTD_NORETURN
    #define QSTD_LIKELY(x)   (x)
    #define QSTD_UNLIKELY(x) (x)
#endif

/* Common macros */
#define QSTD_UNUSED(x)  ((void)(x))
#define QSTD_ARRAY_LEN(a) (sizeof(a) / sizeof((a)[0]))
#define QSTD_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define QSTD_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define QSTD_CLAMP(x, lo, hi) QSTD_MIN(QSTD_MAX((x), (lo)), (hi))
#define QSTD_SWAP(T, a, b) do { T _tmp = (a); (a) = (b); (b) = _tmp; } while (0)

/* Common typedefs (C-compatible) */
typedef unsigned char  qstd_byte;
typedef int64_t        qstd_i64;
typedef uint64_t       qstd_u64;
typedef int32_t        qstd_i32;
typedef uint32_t       qstd_u32;
typedef int16_t        qstd_i16;
typedef uint16_t       qstd_u16;
typedef int8_t         qstd_i8;
typedef uint8_t        qstd_u8;
typedef float          qstd_f32;
typedef double         qstd_f64;

#endif /* QSTD_TYPES_H */