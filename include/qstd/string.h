#pragma once
#ifndef QSTD_STRING_H
#define QSTD_STRING_H

#include "types.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---------- C API ---------- */

QSTD_INLINE int qstd_str_eq(const char* a, const char* b) {
    if (a == b) return 1;
    if (!a || !b) return 0;
    return strcmp(a, b) == 0;
}

QSTD_INLINE int qstd_str_eq_nocase(const char* a, const char* b) {
    if (a == b) return 1;
    if (!a || !b) return 0;
#if defined(_MSC_VER)
    return _stricmp(a, b) == 0;
#else
    return strcasecmp(a, b) == 0;
#endif
}

QSTD_INLINE int qstd_str_starts_with(const char* s, const char* prefix) {
    if (!s || !prefix) return 0;
    size_t n = strlen(prefix);
    return strncmp(s, prefix, n) == 0;
}

QSTD_INLINE int qstd_str_ends_with(const char* s, const char* suffix) {
    if (!s || !suffix) return 0;
    size_t ls = strlen(s), lf = strlen(suffix);
    if (lf > ls) return 0;
    return memcmp(s + ls - lf, suffix, lf) == 0;
}

QSTD_INLINE int qstd_str_contains(const char* s, const char* sub) {
    if (!s || !sub) return 0;
    return strstr(s, sub) != NULL;
}

QSTD_INLINE char* qstd_str_trim(char* s) {
    if (!s) return NULL;
    while (*s && isspace((unsigned char)*s)) s++;
    if (!*s) return s;
    char* end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) *end-- = '\0';
    return s;
}

QSTD_INLINE void qstd_str_to_lower(char* s) {
    if (!s) return;
    for (; *s; ++s) *s = (char)tolower((unsigned char)*s);
}

QSTD_INLINE void qstd_str_to_upper(char* s) {
    if (!s) return;
    for (; *s; ++s) *s = (char)toupper((unsigned char)*s);
}

/* Replace all occurrences of `from` with `to` in `src` -> writes into dst (must be large enough) */
QSTD_INLINE int qstd_str_replace(const char* src, const char* from, const char* to,
                                  char* dst, size_t dst_size) {
    if (!src || !from || !to || !dst || dst_size == 0) return -1;
    size_t from_len = strlen(from);
    if (from_len == 0) return -1;
    size_t to_len = strlen(to);
    size_t out = 0;
    const char* p = src;
    while (*p) {
        if (strncmp(p, from, from_len) == 0) {
            if (out + to_len + 1 > dst_size) return -1;
            memcpy(dst + out, to, to_len);
            out += to_len;
            p += from_len;
        } else {
            if (out + 2 > dst_size) return -1;
            dst[out++] = *p++;
        }
    }
    dst[out] = '\0';
    return 0;
}

/* Split string by delimiter, returns number of parts written into `out`, caller owns `out` */
QSTD_INLINE int qstd_str_split(const char* s, char delim, char** out, int max_parts) {
    if (!s || !out || max_parts <= 0) return 0;
    int count = 0;
    const char* start = s;
    while (count < max_parts) {
        const char* p = strchr(start, delim);
        size_t len = p ? (size_t)(p - start) : strlen(start);
        out[count] = (char*)malloc(len + 1);
        if (!out[count]) return count;
        memcpy(out[count], start, len);
        out[count][len] = '\0';
        count++;
        if (!p) break;
        start = p + 1;
    }
    return count;
}

#ifdef __cplusplus
} /* extern "C" */

#include <string>
#include <vector>

namespace qstd {

/* ---------- C++ API ---------- */

inline std::string to_string(int v)               { return std::to_string(v); }
inline std::string to_string(long v)              { return std::to_string(v); }
inline std::string to_string(long long v)         { return std::to_string(v); }
inline std::string to_string(unsigned v)          { return std::to_string(v); }
inline std::string to_string(double v)            { return std::to_string(v); }
inline std::string to_string(float v)             { return std::to_string(v); }

inline std::string trim(const std::string& s) {
    size_t a = 0, b = s.size();
    while (a < b && std::isspace((unsigned char)s[a])) ++a;
    while (b > a && std::isspace((unsigned char)s[b - 1])) --b;
    return s.substr(a, b - a);
}

inline std::string to_lower(std::string s) {
    for (auto& c : s) c = (char)std::tolower((unsigned char)c);
    return s;
}

inline std::string to_upper(std::string s) {
    for (auto& c : s) c = (char)std::toupper((unsigned char)c);
    return s;
}

inline bool starts_with(const std::string& s, const std::string& p) {
    return s.size() >= p.size() && s.compare(0, p.size(), p) == 0;
}
inline bool ends_with(const std::string& s, const std::string& p) {
    return s.size() >= p.size() && s.compare(s.size() - p.size(), p.size(), p) == 0;
}
inline bool contains(const std::string& s, const std::string& p) {
    return s.find(p) != std::string::npos;
}

inline std::string replace(std::string s, const std::string& from, const std::string& to) {
    if (from.empty()) return s;
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != std::string::npos) {
        s.replace(pos, from.size(), to);
        pos += to.size();
    }
    return s;
}

inline std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::string cur;
    for (char c : s) {
        if (c == delim) { out.push_back(cur); cur.clear(); }
        else cur.push_back(c);
    }
    out.push_back(cur);
    return out;
}

inline std::string join(const std::vector<std::string>& v, const std::string& sep) {
    std::string out;
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) out += sep;
        out += v[i];
    }
    return out;
}

/* Simple format (printf-style) -> std::string */
template <typename... Args>
inline std::string format(const char* fmt, Args... args) {
    int n = std::snprintf(nullptr, 0, fmt, args...);
    if (n <= 0) return {};
    std::string out((size_t)n, '\0');
    std::snprintf(&out[0], (size_t)n + 1, fmt, args...);
    return out;
}

}
#endif /* __cplusplus */

#endif /* QSTD_STRING_H */