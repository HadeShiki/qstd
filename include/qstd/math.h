#pragma once
#ifndef QSTD_MATH_H
#define QSTD_MATH_H

#include "types.h"

/* C API */
QSTD_INLINE int qstd_is_pow2(qstd_u32 x) { return x && !(x & (x - 1)); }

QSTD_INLINE qstd_u32 qstd_next_pow2(qstd_u32 x) {
    if (x == 0) return 1;
    x--;
    x |= x >> 1; x |= x >> 2; x |= x >> 4; x |= x >> 8; x |= x >> 16;
    return x + 1;
}

QSTD_INLINE int qstd_abs_i(int x) { return x < 0 ? -x : x; }
QSTD_INLINE int qstd_sign_i(int x) { return (x > 0) - (x < 0); }

QSTD_INLINE double qstd_map(double v, double in_lo, double in_hi,
                             double out_lo, double out_hi) {
    if (in_hi == in_lo) return out_lo;
    return out_lo + (v - in_lo) * (out_hi - out_lo) / (in_hi - in_lo);
}

QSTD_INLINE double qstd_lerp(double a, double b, double t) {
    return a + (b - a) * t;
}

#ifdef __cplusplus
#include <cmath>
#include <algorithm>
#include <type_traits>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace qstd {

template <typename T>
inline T clamp(T v, T lo, T hi) {
    return (std::max)(lo, (std::min)(v, hi));
}

template <typename T>
inline T lerp(T a, T b, double t) { return (T)(a + (b - a) * t); }

inline bool approx_equal(double a, double b, double eps = 1e-9) {
    return std::fabs(a - b) < eps;
}

inline bool is_zero(double v, double eps = 1e-9) { return std::fabs(v) < eps; }

}
#endif

#endif /* QSTD_MATH_H */