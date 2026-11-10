#pragma once
#ifndef QSTD_CONTAINER_H
#define QSTD_CONTAINER_H

#include "types.h"

#ifdef __cplusplus
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <algorithm>

namespace qstd {

/* Check if key exists in map */
template <typename Map, typename Key>
inline bool has_key(const Map& m, const Key& k) {
    return m.find(k) != m.end();
}

/* Get value or default if not present */
template <typename Map, typename Key>
inline typename Map::mapped_type
get_or(const Map& m, const Key& k, const typename Map::mapped_type& def = {}) {
    auto it = m.find(k);
    return it != m.end() ? it->second : def;
}

/* Remove all matching values from vector */
template <typename T>
inline void erase_value(std::vector<T>& v, const T& val) {
    v.erase(std::remove(v.begin(), v.end(), val), v.end());
}

/* Remove by predicate */
template <typename T, typename Pred>
inline void erase_if(std::vector<T>& v, Pred pred) {
    v.erase(std::remove_if(v.begin(), v.end(), pred), v.end());
}

/* Return vector with elements that satisfy pred */
template <typename T, typename Pred>
inline std::vector<T> filter(const std::vector<T>& v, Pred pred) {
    std::vector<T> out;
    for (const auto& x : v) if (pred(x)) out.push_back(x);
    return out;
}

/* Map each element through fn -> vector of results */
template <typename T, typename Fn>
inline auto map(const std::vector<T>& v, Fn fn)
    -> std::vector<decltype(fn(v[0]))> {
    std::vector<decltype(fn(v[0]))> out;
    out.reserve(v.size());
    for (const auto& x : v) out.push_back(fn(x));
    return out;
}

/* Sum of elements */
template <typename T>
inline T sum(const std::vector<T>& v) {
    T s{};
    for (const auto& x : v) s += x;
    return s;
}

/* Iterate with index */
template <typename Container, typename Fn>
inline void for_each_indexed(const Container& c, Fn fn) {
    size_t i = 0;
    for (const auto& x : c) fn(i++, x);
}

}
#endif

#endif /* QSTD_CONTAINER_H */