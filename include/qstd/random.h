#pragma once
#ifndef QSTD_RANDOM_H
#define QSTD_RANDOM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Seed the random generator (thread-safe on most platforms via rand) */
QSTD_INLINE void qstd_srand(unsigned seed) { srand(seed); }

/* Random int in [lo, hi] inclusive */
QSTD_INLINE int qstd_rand_int(int lo, int hi) {
    if (lo >= hi) return lo;
    return lo + rand() % (hi - lo + 1);
}

/* Random double in [0, 1) */
QSTD_INLINE double qstd_rand_double(void) {
    return (double)rand() / ((double)RAND_MAX + 1.0);
}

/* Random double in [lo, hi) */
QSTD_INLINE double qstd_rand_range(double lo, double hi) {
    return lo + qstd_rand_double() * (hi - lo);
}

#ifdef __cplusplus
} /* extern "C" */

#include <random>
#include <algorithm>
#include <cstdlib>

namespace qstd {

/* Thread-safe, high-quality RNG */
inline std::mt19937_64& rng() {
    static thread_local std::mt19937_64 gen{std::random_device{}()};
    return gen;
}

inline int rand_int(int lo, int hi) {
    if (lo >= hi) return lo;
    std::uniform_int_distribution<int> d(lo, hi);
    return d(rng());
}

inline double rand_double(double lo = 0.0, double hi = 1.0) {
    std::uniform_real_distribution<double> d(lo, hi);
    return d(rng());
}

template <typename T>
inline void shuffle(T* begin, T* end) {
    std::shuffle(begin, end, rng());
}

/* Pick random element from container with [] */
template <typename Container>
inline auto pick(const Container& c) -> decltype(c[0]) {
    return c[static_cast<size_t>(rand_int(0, (int)c.size() - 1))];
}

}
#endif

#endif /* QSTD_RANDOM_H */