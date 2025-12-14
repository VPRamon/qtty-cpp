# qtty-cpp: Modern C++ Wrapper for qtty-ffi

A type-safe, user-friendly C++ template library wrapping the qtty-ffi physical quantities library.

## Features

- ✨ **Type-safe**: Compile-time unit checking using C++ templates
- 🎯 **User-friendly**: Natural operator syntax (`+`, `-`, `*`, `/`)
- 🔧 **Zero-overhead**: Header-only with inline templates
- 🎨 **Modern C++17**: Using constexpr, user-defined literals, and template metaprogramming
- 🛡️ **Exception-based error handling**: Clear error messages for dimension mismatches
- 📦 **Easy to integrate**: Single header include, automatic FFI library linking
- ✅ **Tested with Google Test**: Comprehensive test suite

## Quick Start

### Prerequisites

- **CMake 3.15+**: For building
- **C++17 or later**: Modern C++ compiler (GCC, Clang, or MSVC)
- **Cargo/Rust**: For building the qtty-ffi library
- **Internet connection**: First build will fetch Google Test automatically

### Installation

```bash
# Clone the repository with submodules
git clone --recurse-submodules <repository-url>
cd qtty-cpp

# Build
mkdir build && cd build
cmake ..
make -j$(nproc)

# Run tests
ctest --output-on-failure
# or run tests directly
./test_ffi
```

### Basic Usage

```cpp
#include "qtty/qtty_ffi.hpp"
using namespace qtty;

int main() {
    // Create quantities using constructors
    Meter distance(1000.0);
    Second time(20.0);
    
    // Or use user-defined literals
    auto height = 5.5_m;
    auto duration = 10.0_s;
    
    // Perform arithmetic operations
    auto total_distance = distance + height;
    auto doubled = distance * 2.0;
    
    // Unit conversions are type-safe
    Kilometer km = distance.to<Kilometer>();
    std::cout << "Distance: " << km.value() << " km\n";
    
    // Create compound units (velocity)
    auto velocity = distance / time;
    std::cout << "Velocity: " << velocity.value() << " m/s\n";
    
    // Comparisons work naturally
    if (distance > height) {
        std::cout << "Distance is greater\n";
    }
    
    // Use compound assignment operators
    distance += 100.0_m;
    distance *= 2.0;
    
    // Absolute value and negation
    Meter negative(-5.0);
    auto positive = negative.abs();
    
    return 0;
}
```

## Supported Units

### Length
- `Meter` (m)
- `Kilometer` (km)

### Time
- `Second` (s)
- `Minute` (min)
- `Hour` (h)
- `Day` (day)

### Angular
- `Radian` (rad)
- `Degree` (deg)

### Compound Units
- `Velocity<Length, Time>` - Created by dividing length by time
  - `MeterPerSecond` - m/s
  - `KilometerPerHour` - km/h

## User-Defined Literals

```cpp
using namespace qtty;

// Length
auto m1 = 10.0_m;      // Meter
auto km1 = 5.0_km;     // Kilometer

// Time  
auto s1 = 30.0_s;      // Second
auto min1 = 2.0_min;   // Minute
auto h1 = 1.5_h;       // Hour

// Angular
auto rad1 = 3.14_rad;  // Radian
auto deg1 = 90.0_deg;  // Degree
```

## Operations

### Arithmetic
```cpp
Meter a(10.0), b(5.0);

// Same-unit operations
auto sum = a + b;        // 15 m
auto diff = a - b;       // 5 m

// Scalar operations
auto scaled = a * 2.0;   // 20 m
auto divided = a / 2.0;  // 5 m
```

### Comparisons
```cpp
Meter a(10.0), b(5.0);

bool equal = (a == b);   // false
bool not_equal = (a != b); // true
bool less = (b < a);     // true
bool greater = (a > b);  // true
```

### Compound Assignments
```cpp
Meter distance(100.0);

distance += 50.0_m;      // 150 m
distance -= 25.0_m;      // 125 m
distance *= 2.0;         // 250 m
distance /= 5.0;         // 50 m
```

### Unit Conversion
```cpp
Meter m(1000.0);
Kilometer km = m.to<Kilometer>();  // 1.0 km

// Convert back
Meter m2 = km.to<Meter>();         // 1000.0 m
```

### Utility Functions
```cpp
Meter negative(-5.5);
auto positive = negative.abs();    // 5.5 m

auto negated = -negative;          // 5.5 m
```

## Architecture

### Template-Based Design

The library uses C++ templates to provide type safety at compile time:

```cpp
template<typename UnitTag>
class Quantity {
    // Core quantity implementation
};

// Type aliases for convenience
using Meter = Quantity<MeterTag>;
using Second = Quantity<SecondTag>;
```

### Header Structure

```
include/qtty/
├── qtty_ffi.hpp           # Main header (include this)
├── ffi_core.hpp           # Core Quantity template
├── literals.hpp           # User-defined literals
└── units/
    ├── length_ffi.hpp     # Length units
    ├── time_ffi.hpp       # Time units
    ├── angular_ffi.hpp    # Angular units
    └── velocity_ffi.hpp   # Compound velocity units
```

### Exception Handling

The library throws exceptions for error conditions:

```cpp
try {
    Meter m(100.0);
    // This would throw IncompatibleDimensionsError
    // if trying to convert length to time
    Second s = m.to<Second>();
} catch (const qtty::IncompatibleDimensionsError& e) {
    std::cerr << "Dimension mismatch: " << e.what() << '\n';
} catch (const qtty::QttyException& e) {
    std::cerr << "Qtty error: " << e.what() << '\n';
}
```

## Integration with CMake

To use qtty-cpp in your project:

```cmake
# Add qtty-cpp as a subdirectory
add_subdirectory(path/to/qtty-cpp)

# Link against the qtty_cpp interface library
target_link_libraries(your_target PRIVATE qtty_cpp)
```

The `qtty_cpp` target is an `INTERFACE` library that automatically:
- Provides the include directories for both C++ headers and C FFI headers
- Links against the qtty-ffi shared library
- Sets up proper RPATH for runtime library location

## Design Principles

1. **Zero-Cost Abstraction**: Templates are resolved at compile time with no runtime overhead
2. **Type Safety**: Incompatible unit operations are caught at compile time
3. **Natural Syntax**: C++ operators work as expected with quantities
4. **Easy Maintenance**: Adding new units requires only:
   - A tag struct (e.g., `struct MeterTag {}`)
   - A `UnitTraits` specialization with the C API unit ID
   - A type alias (e.g., `using Meter = Quantity<MeterTag>`)
   - Optional user-defined literals

## Requirements

- **C++17 or later**: For constexpr improvements and template features
- **CMake 3.15+**: For building and FetchContent support
- **Cargo/Rust**: For building the qtty-ffi library
- **GCC/Clang/MSVC**: Any modern C++ compiler
- **Google Test**: Automatically fetched by CMake (internet required on first build)

## Project Structure

```
qtty-cpp/
├── CMakeLists.txt          # Build configuration with Google Test integration
├── README.md               # This file
├── .gitignore             # Git ignore patterns
├── include/qtty/          # C++ wrapper headers (header-only)
│   ├── qtty_ffi.hpp       # Main header
│   ├── ffi_core.hpp       # Core Quantity template
│   ├── literals.hpp       # User-defined literals
│   └── units/             # Unit-specific headers
├── examples/
│   └── demo.cpp           # Usage examples
├── tests/
│   └── test_ffi.cpp       # Google Test suite
└── qtty/                  # Git submodule (Rust FFI library)
```

## Testing

The project uses [Google Test](https://github.com/google/googletest) for comprehensive unit testing.

### Running Tests

```bash
# Using CTest (preferred)
cd build
ctest --output-on-failure

# Run with verbose output
ctest -V

# Run tests directly
./test_ffi

# Run specific test
./test_ffi --gtest_filter=QttyTest.MeterConstruction
```

### Test Coverage

The test suite covers:
- ✅ Unit construction (direct and literals)
- ✅ Arithmetic operations (+, -, *, /)
- ✅ Comparison operators (==, !=, <, >, <=, >=)
- ✅ Unit conversions (length, time, angular)
- ✅ Compound assignment (+=, -=, *=, /=)
- ✅ Velocity creation (compound units)
- ✅ Utility methods (abs, negation)
- ✅ Exception handling

### Test Output Example

```
[==========] Running 12 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 12 tests from QttyTest
[ RUN      ] QttyTest.MeterConstruction
[       OK ] QttyTest.MeterConstruction (0 ms)
[ RUN      ] QttyTest.MeterArithmetic
[       OK ] QttyTest.MeterArithmetic (0 ms)
...
[==========] 12 tests from 1 test suite ran. (X ms total)
[  PASSED  ] 12 tests.
```

## Contributing

When adding new units:

1. Define the unit in the C FFI layer (qtty-ffi)
2. Create a tag struct in the appropriate header
3. Specialize `UnitTraits` with the unit ID
4. Add a type alias for convenience
5. Add user-defined literals if appropriate
6. Update tests

## License

See the LICENSE file in the qtty submodule for details.

## Version

- **C++ Wrapper**: v0.1.0
- **FFI ABI**: Check with `qtty::abi_version()`

## Acknowledgments

Built on top of the excellent [qtty](https://github.com/sidereal-dave/qtty) Rust library by providing a modern C++ interface.
