#pragma once
#ifndef QSTD_FILE_H
#define QSTD_FILE_H

#include "types.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Read entire file into malloc'd buffer. Caller frees. Returns NULL on error. */
QSTD_INLINE char* qstd_file_read_all(const char* path, size_t* out_size) {
    FILE* f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz < 0) { fclose(f); return NULL; }
    char* buf = (char*)malloc((size_t)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    size_t rd = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    buf[rd] = '\0';
    if (out_size) *out_size = rd;
    return buf;
}

QSTD_INLINE int qstd_file_write_all(const char* path, const void* data, size_t size) {
    FILE* f = fopen(path, "wb");
    if (!f) return -1;
    size_t wr = fwrite(data, 1, size, f);
    fclose(f);
    return wr == size ? 0 : -1;
}

QSTD_INLINE int qstd_file_exists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0;
}

QSTD_INLINE long qstd_file_size(const char* path) {
    struct stat st;
    if (stat(path, &st) != 0) return -1;
    return (long)st.st_size;
}

#ifdef __cplusplus
} /* extern "C" */

#include <fstream>
#include <string>
#include <sstream>

namespace qstd {

inline bool read_file(const std::string& path, std::string& out) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return false;
    std::ostringstream ss;
    ss << f.rdbuf();
    out = ss.str();
    return true;
}

inline std::string read_file(const std::string& path) {
    std::string s;
    read_file(path, s);
    return s;
}

inline bool write_file(const std::string& path, const std::string& content) {
    std::ofstream f(path, std::ios::binary);
    if (!f) return false;
    f.write(content.data(), (std::streamsize)content.size());
    return (bool)f;
}

inline bool file_exists(const std::string& path) {
    return qstd_file_exists(path.c_str()) != 0;
}

}
#endif

#endif /* QSTD_FILE_H */