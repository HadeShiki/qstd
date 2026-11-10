#pragma once
#ifndef QSTD_MEMORY_H
#define QSTD_MEMORY_H

#include "types.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Safe free: free(p) then p = NULL (macro) */
#define QSTD_FREE(p) do { free(p); (p) = QSTD_NULL; } while (0)

QSTD_INLINE void* qstd_alloc(size_t size) {
    if (size == 0) size = 1;
    return malloc(size);
}

QSTD_INLINE void* qstd_calloc(size_t count, size_t size) {
    return calloc(count ? count : 1, size ? size : 1);
}

QSTD_INLINE void* qstd_realloc(void* p, size_t size) {
    return realloc(p, size ? size : 1);
}

#ifdef __cplusplus
} /* extern "C" */

#include <memory>

namespace qstd {

/* Alias for readability */
template <typename T> using uptr = std::unique_ptr<T>;
template <typename T> using sptr = std::shared_ptr<T>;
template <typename T> using wptr = std::weak_ptr<T>;

template <typename T, typename... Args>
inline std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

/* RAII deleter for C malloc'd buffers */
struct FreeDeleter {
    void operator()(void* p) const { free(p); }
};
using cbuf = std::unique_ptr<char, FreeDeleter>;

}
#endif

#endif /* QSTD_MEMORY_H */