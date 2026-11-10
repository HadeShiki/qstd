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