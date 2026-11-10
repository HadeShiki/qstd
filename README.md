# qstd

A lightweight, header-mostly C++ utility library. Zero dependencies, C++11+, works in C too.

[![C++11](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)]()

## Features

- **String** — `trim`, `split`, `join`, `replace`, `starts_with`, `format`, ...
- **File I/O** — `read_file`, `write_file`, `file_exists` (one-liners)
- **Time** — `Stopwatch`, monotonic clock, timestamp formatting
- **Logging** — leveled, colored, thread-safe
- **Random** — thread-safe `mt19937_64` wrapper
- **Math** — `clamp`, `lerp`, `approx_equal`, pow2 helpers
- **Container** — `filter`, `map`, `sum`, `erase_if`, `get_or`
- **Memory** — `make_unique`, smart pointer aliases, RAII buffer

## Quick Start

### 1. Clone

```bash
git clone https://github.com/HadeShiki/qstd.git
```

### 2. Use it

```cpp
#include "qstd/qstd.h"

int main() {
    qstd_log_set_level(QSTD_LOG_DEBUG);

    qstd::Stopwatch sw;

    qstd::write_file("hello.txt", "Hello qstd!");
    std::string txt = qstd::read_file("hello.txt");

    auto words = qstd::split(qstd::trim(txt), ' ');
    QSTD_LOG_INFO("Found %zu words", words.size());
    QSTD_LOG_INFO("Took %.3f ms", sw.elapsed_ms());

    return 0;
}
```

### 3. Build

### CMake (recommended):

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cd build && ctest --output-on-failure
```

### g++ / clang++:

```bash
g++ -std=c++11 -O2 -Iinclude main.cpp src/log.cpp -o app -pthread
./app
```

### MSVC:

```bash
cl /std:c++14 /EHsc /Iinclude main.cpp src\log.cpp /Fe:app.exe
```

## Compiler Support

| Compiler   | Minimum Version | C++ Standard | Status | Notes                          |
|------------|-----------------|--------------|--------|--------------------------------|
| GCC        | 4.8             | C++11        | ✅     | Full support                   |
| GCC        | 7.0+            | C++17        | ✅     | Recommended                    |
| Clang      | 3.4             | C++11        | ✅     | Full support                   |
| Clang      | 5.0+            | C++17        | ✅     | Recommended                    |
| MSVC       | 2015 (v1900)    | C++11        | ✅     | Partial C++11                  |
| MSVC       | 2017 (v1910)+   | C++14        | ✅     | Recommended                    |
| MSVC       | 2019 (v1920)+   | C++17        | ✅     | Full support                   |
| MinGW-w64  | 5.0+            | C++11        | ✅     | POSIX threads required         |
| Apple Clang| 8.0+            | C++11        | ✅     | macOS 10.12+                   |
| Intel C++  | 2019+           | C++11        | ⚠️     | Not officially tested          |

## License

MIT — see [LICENSE](LICENSE).