# qtty-cpp

qtty-cpp is a C++17 library for working with physical quantities using unit-safe types. It provides a header-only C++ API backed by the Rust `qtty-ffi` conversion engine (via a C FFI).

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/CMake-3.15%2B-064F8C.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-See%20qtty-green.svg)](qtty/LICENSE)

## Features

- Strong types per unit (e.g., `Meter`, `Second`) to prevent mixing incompatible dimensions
- Unit conversion via `Quantity::to<T>()` using the Rust `qtty-ffi` engine
- User-defined literals for convenient construction (e.g., `10.0_km`, `5.0_s`)
- Generated unit/type/literal headers derived from `qtty/qtty-ffi/include/qtty_ffi.h`
- CMake target (`qtty_cpp`) for straightforward integration

## Requirements

- CMake 3.15+
- C++17 compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Python 3.6+ (wrapper generation)
- Rust/Cargo (builds `qtty-ffi`)

## Build and Test

```bash
git clone --recurse-submodules <repo-url>
cd qtty-cpp

cmake -S . -B build
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/demo
```

If you cloned without submodules:

```bash
git submodule update --init --recursive
```

## Usage

```cpp
#include <iostream>
#include "qtty/qtty.hpp"

using namespace qtty;

int main() {
    auto distance = 100.0_km;
    auto time = 2.0_h;

    auto speed = distance / time; // compound type (e.g., KilometerPerHour)
    std::cout << speed.value() << " km/h\n";

    Meter m = distance.to<Meter>();
    std::cout << m.value() << " m\n";
}
```

### Compound Units

Division creates compound quantity types (e.g., velocity). The FFI conversion layer only supports base dimensions, so compound types cannot be converted directly (for example, `m/s` to `km/h`). See `include/qtty/units/velocity.hpp` and `docs/architecture.md`.

## Documentation

- `docs/README.md` (documentation index)
- `docs/QUICK_REFERENCE.md` (one-page usage summary)
- `docs/api/quantities.md` (API reference)
- `docs/build-and-testing.md` (build, test, troubleshooting)
- `docs/extending-units.md` (adding units)
- `docs/architecture.md` (design overview)

## Integration

### Add as a Subdirectory

```cmake
add_subdirectory(path/to/qtty-cpp)
target_link_libraries(your_target PRIVATE qtty_cpp)
```

### Install and Use `find_package`

```bash
cmake --install build
```

```cmake
find_package(qtty_cpp REQUIRED)
target_link_libraries(your_target PRIVATE qtty::qtty_cpp)
```

## License

This repository wraps the upstream `qtty` project (git submodule in `qtty/`). See `qtty/LICENSE` for licensing details.
