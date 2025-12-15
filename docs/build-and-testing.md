# Build and Testing Guide

This guide provides comprehensive instructions for building qtty-cpp, running tests, and troubleshooting common issues.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Quick Start](#quick-start)
- [Build Process Details](#build-process-details)
- [Running Tests](#running-tests)
- [Testing Strategy](#testing-strategy)
- [Troubleshooting](#troubleshooting)
- [Advanced Build Options](#advanced-build-options)

## Prerequisites

### Required Tools

| Tool | Minimum Version | Purpose |
|------|----------------|---------|
| **CMake** | 3.15+ | Build system orchestration |
| **C++ Compiler** | C++17 support | Compiling C++ code (GCC 7+, Clang 5+, MSVC 2017+) |
| **Cargo/Rust** | Latest stable | Building the qtty-ffi Rust library |
| **Python 3** | 3.6+ | Running the code generator (`gen_cpp_units.py`) |
| **Git** | Any recent | Cloning repository and submodules |

### Operating System Support

- **Linux**: Fully supported (tested on Ubuntu, Fedora, Arch)
- **macOS**: Fully supported (tested on macOS 10.15+)
- **Windows**: Supported with MSVC (MinGW/Cygwin may work but untested)

### Internet Connection

First build requires internet access to:
- Fetch Google Test framework (via CMake FetchContent)
- Download Rust dependencies (via Cargo)

Subsequent builds use cached dependencies.

## Quick Start

### 1. Clone Repository

```bash
git clone --recurse-submodules <repository-url>
cd qtty-cpp
```

**Important**: The `--recurse-submodules` flag is required to fetch the qtty-ffi Rust library.

If you already cloned without submodules:

```bash
git submodule update --init --recursive
```

### 2. Build

```bash
cmake -S . -B build
cmake --build build --parallel
```

On Windows with MSVC:

```cmd
cmake -S . -B build
cmake --build build --config Release
```

### 3. Run Tests

```bash
# Using CTest (recommended)
ctest --test-dir build --output-on-failure

# Or run test executable directly
./build/test_ffi
```

### 4. Run Demo

```bash
./build/demo
```

Expected output:

```
=== qtty-cpp Demo ===
FFI ABI Version: 1

1. Distance Conversion:
   Distance: 1500 m
   Distance: 1.5 km

2. Using Literals:
   Height: 10.5 m
   Width: 5 m
   Sum: 15.5 m
...
```

## Build Process Details

The build orchestrates three tools: Python, Cargo, and CMake. Understanding this flow helps diagnose issues.

### Build Pipeline

```
Step 1: Header Generation
- Python runs gen_cpp_units.py
- Parses qtty/qtty-ffi/include/qtty_ffi.h
- Generates include/qtty/units/*.hpp
- Generates include/qtty/literals.hpp

Step 2: Rust Library Compilation
- Cargo builds qtty-ffi crate
- Output: qtty/target/release/libqtty_ffi.{so,dylib,dll}
- Depends on Step 1 (CMake dependency)

Step 3: C++ Integration
- CMake creates interface library qtty_cpp
- Links against qtty_ffi
- Sets include paths
- Configures RPATH for runtime library location

Step 4: Build Executables
- demo executable
- test_ffi executable (links Google Test)
```

### CMake Targets

Run individual build steps:

```bash
# Generate C++ headers only
cmake --build . --target gen_cpp_units

# Build Rust library only
cmake --build . --target build_qtty_ffi

# Build demo only
cmake --build . --target demo

# Build tests only
cmake --build . --target test_ffi
```

### What Gets Built

After a successful build, the `build/` directory contains:

```
build/
  demo                        # Demo executable
  test_ffi                    # Test executable
  lib/                        # (empty, INTERFACE library)
  _deps/googletest-build/     # Google Test build artifacts
```

The Rust library is built in the submodule:

```
qtty/target/release/
  libqtty_ffi.so    (Linux)
  libqtty_ffi.dylib (macOS)
  qtty_ffi.dll      (Windows)
```

## Running Tests

### Using CTest (Recommended)

CTest integrates with Google Test for flexible test execution:

```bash
cd build

# Run all tests
ctest

# Verbose output
ctest -V

# Show test output only on failure
ctest --output-on-failure

# Run tests matching a pattern
ctest -R Length

# Run tests in parallel
ctest -j8
```

### Direct Test Execution

Run the test binary directly for more Google Test options:

```bash
cd build

# Run all tests
./test_ffi

# List available tests
./test_ffi --gtest_list_tests

# Run specific test suite
./test_ffi --gtest_filter=LengthDimensionTest.*

# Run specific test
./test_ffi --gtest_filter=LengthDimensionTest.MeterConstruction

# Run multiple patterns
./test_ffi --gtest_filter=*Conversion*:*Comparison*

# Exclude tests
./test_ffi --gtest_filter=-*Precision*

# Repeat tests (useful for flaky test detection)
./test_ffi --gtest_repeat=100

# Show detailed output
./test_ffi --gtest_verbose

# Run with color output
./test_ffi --gtest_color=yes
```

### Test Output Format

Successful test run:

```
[==========] Running 37 tests from 9 test suites.
[----------] Global test environment set-up.
[----------] 5 tests from LengthDimensionTest
[ RUN      ] LengthDimensionTest.MeterConstruction
[       OK ] LengthDimensionTest.MeterConstruction (0 ms)
[ RUN      ] LengthDimensionTest.MeterArithmetic
[       OK ] LengthDimensionTest.MeterArithmetic (0 ms)
...
[----------] 5 tests from LengthDimensionTest (1 ms total)
...
[==========] 37 tests from 9 test suites ran. (12 ms total)
[  PASSED  ] 37 tests.
```

Failed test example:

```
[ RUN      ] LengthDimensionTest.MeterArithmetic
/path/to/test_length.cpp:17: Failure
Expected equality of these values:
  sum.value()
    Which is: 12
  13.0
[  FAILED  ] LengthDimensionTest.MeterArithmetic (1 ms)
```

## Testing Strategy

The qtty-cpp test suite is organized into nine test suites covering different aspects of the library.

### Test File Organization

**Location**: [tests/](../tests/)

| File | Test Suite | Purpose | Test Count |
|------|-----------|---------|------------|
| [test_length.cpp](../tests/test_length.cpp) | `LengthDimensionTest` | Length unit operations and conversions | 5 |
| [test_time.cpp](../tests/test_time.cpp) | `TimeDimensionTest` | Time unit operations and conversions | 4 |
| [test_angular.cpp](../tests/test_angular.cpp) | `AngularDimensionTest` | Angular unit operations and conversions | 4 |
| [test_mass.cpp](../tests/test_mass.cpp) | `MassDimensionTest` | Mass unit operations and conversions | 4 |
| [test_power.cpp](../tests/test_power.cpp) | `PowerDimensionTest` | Power unit operations and conversions | 4 |
| [test_derived.cpp](../tests/test_derived.cpp) | `DerivedQuantityTest` | Compound units (velocity) | 1 |
| [test_operations.cpp](../tests/test_operations.cpp) | `QuantityOperationsTest` | Arithmetic and utility operations | 8 |
| [test_dimension_safety.cpp](../tests/test_dimension_safety.cpp) | `DimensionSafetyTest` | Exception handling | 1 |
| [test_precision.cpp](../tests/test_precision.cpp) | `PrecisionEdgeCaseTest` | Numerical precision edge cases | 6 |

### Test Suite Descriptions

#### LengthDimensionTest

Tests length units including metric, imperial, and astronomical scales.

**Key Tests**:
- `MeterConstruction` - Constructor and literal creation
- `MeterArithmetic` - Addition, subtraction, multiplication, division
- `MeterComparison` - All comparison operators
- `LengthUnitConversions` - Meter <-> Kilometer, millimeter, inch, mile
- `AstronomicalLengthUnits` - AU, light-year, parsec conversions
- `SmallLengthUnits` - Nanometer, micrometer conversions

**Example Test** (from [test_length.cpp](../tests/test_length.cpp)):

```cpp
TEST_F(LengthDimensionTest, LengthUnitConversions) {
    Meter m(1000.0);
    Kilometer km = m.to<Kilometer>();
    EXPECT_NEAR(km.value(), 1.0, 1e-12);

    Meter m2 = km.to<Meter>();
    EXPECT_NEAR(m2.value(), 1000.0, 1e-9);
    
    auto inch_val = 12.0_in;
    Centimeter cm = inch_val.to<Centimeter>();
    EXPECT_NEAR(cm.value(), 30.48, 1e-9);
}
```

#### TimeDimensionTest

Tests time units from nanoseconds to days.

**Key Tests**:
- `SecondConstruction` - Constructor and literal creation
- `TimeUnitConversions` - Second <-> Minute, Hour, Day
- `SmallTimeUnits` - Millisecond, microsecond, nanosecond
- `CompoundTimeOperations` - Arithmetic operations

#### AngularDimensionTest

Tests angular units including degrees, radians, arcminutes, and arcseconds.

**Key Tests**:
- `RadianConstruction` - Constructor and literal creation
- `AngularConversions` - Radian <-> Degree conversions
- `ArcminArcSecConversions` - Arcminute and arcsecond conversions
- `AngularArithmetic` - Addition and scalar operations

#### MassDimensionTest

Tests mass units in metric and imperial systems.

**Key Tests**:
- `KilogramConstruction` - Constructor and literal creation
- `MassUnitConversions` - Kilogram <-> Gram, Ton, Pound
- `SmallMassUnits` - Milligram conversions
- `MassComparison` - Comparison operators

#### PowerDimensionTest

Tests power units including watts and horsepower.

**Key Tests**:
- `WattConstruction` - Constructor and literal creation
- `PowerUnitConversions` - Watt <-> Kilowatt, Megawatt, Horsepower
- `PowerArithmetic` - Arithmetic operations
- `PowerComparison` - Comparison operators

#### DerivedQuantityTest

Tests compound units created by dividing quantities.

**Key Tests**:
- `VelocityCreation` - Creating velocity from length/time division

**Example** (from [test_derived.cpp](../tests/test_derived.cpp)):

```cpp
TEST_F(DerivedQuantityTest, VelocityCreation) {
    Meter distance(100.0);
    Second time(20.0);
    auto velocity = distance / time;
    
    EXPECT_NEAR(velocity.value(), 5.0, 1e-12);
    
    Velocity<Meter, Second> v1(10.0);
    EXPECT_EQ(v1.value(), 10.0);
}
```

#### QuantityOperationsTest

Tests arithmetic, utility, and compound assignment operations across all unit types.

**Key Tests**:
- `Addition` - Same-unit addition
- `Subtraction` - Same-unit subtraction
- `ScalarMultiplication` - Quantity * scalar
- `ScalarDivision` - Quantity / scalar
- `CompoundAssignment` - `+=`, `-=`, `*=`, `/=`
- `UnaryMinus` - Negation operator
- `AbsoluteValue` - `abs()` method
- `Comparison` - All comparison operators

#### DimensionSafetyTest

Tests that the library properly throws exceptions for invalid operations.

**Key Tests**:
- `ExceptionHandling` - Verifies `IncompatibleDimensionsError` is thrown for dimension mismatches

**Example** (from [test_dimension_safety.cpp](../tests/test_dimension_safety.cpp)):

```cpp
TEST_F(DimensionSafetyTest, ExceptionHandling) {
    Meter m(100.0);
    
    EXPECT_THROW({
        qtty_quantity_t qty;
        qtty_quantity_make(100.0, UNIT_ID_METER, &qty);
        qtty_quantity_t result;
        int32_t status = qtty_quantity_convert(qty, UNIT_ID_SECOND, &result);
        check_status(status, "Invalid conversion");
    }, IncompatibleDimensionsError);
}
```

#### PrecisionEdgeCaseTest

Tests numerical precision and edge cases.

**Key Tests**:
- `VerySmallValues` - Nanometer-scale values
- `VeryLargeValues` - Light-year and parsec scales
- `NearZeroOperations` - Operations near zero
- `PrecisionMaintenance` - Multiple conversion roundtrips
- `NegativeValues` - Negative quantity operations
- `ZeroComparison` - Comparisons with zero

### Test Fixtures

**Location**: [tests/fixtures.hpp](../tests/fixtures.hpp)

All test suites derive from `QttyTest` base class:

```cpp
class QttyTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class LengthDimensionTest : public QttyTest {};
class TimeDimensionTest : public QttyTest {};
// ... etc.
```

The fixtures use the Google Test framework and import qtty symbols:

```cpp
using namespace qtty;
```

### Testing Philosophy

1. **Comprehensive Coverage**: Every unit type has tests for construction, conversion, and operations
2. **Precision Testing**: Use `EXPECT_NEAR` with appropriate tolerance for floating-point comparisons
3. **Edge Cases**: Test boundary conditions (very large/small values, zero, negative)
4. **Type Safety**: Verify compile-time type safety prevents invalid operations
5. **Error Handling**: Test exception throwing for invalid operations
6. **Real-World Scenarios**: Use realistic conversion factors (e.g., 1 inch = 2.54 cm exactly)

### Adding New Tests

To add a test:

1. Choose appropriate test file (or create new one)
2. Add test using Google Test `TEST_F` macro
3. Update [CMakeLists.txt](../CMakeLists.txt) if adding new file (lines 108-118)
4. Run tests to verify

**Example**:

```cpp
// In test_length.cpp
TEST_F(LengthDimensionTest, MyNewTest) {
    // Arrange
    Meter m(100.0);
    
    // Act
    Kilometer km = m.to<Kilometer>();
    
    // Assert
    EXPECT_NEAR(km.value(), 0.1, 1e-12);
}
```

## Troubleshooting

### Issue: Submodule Not Found

**Error**:
```
CMake Error: qtty/qtty-ffi/include/qtty_ffi.h not found
```

**Solution**:
```bash
git submodule update --init --recursive
cd qtty
cargo build -p qtty-ffi --release
cd ..
```

### Issue: Python Not Found

**Error**:
```
CMake Error: Could not find Python3
```

**Solution**:

Linux/macOS:
```bash
# Install Python 3
sudo apt install python3  # Ubuntu/Debian
brew install python3      # macOS
```

Specify Python path:
```bash
cmake -DPython3_EXECUTABLE=/usr/bin/python3 ..
```

### Issue: Cargo Not Found

**Error**:
```
CMake Error: Could not find cargo
```

**Solution**:

Install Rust:
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source $HOME/.cargo/env
```

Or specify Cargo path:
```bash
cmake -DCARGO_BIN=/path/to/cargo ..
```

### Issue: C++17 Not Supported

**Error**:
```
error: This file requires compiler and library support for the ISO C++ 2017 standard.
```

**Solution**:

Update compiler:
```bash
# Ubuntu
sudo apt install g++-9
export CXX=g++-9

# macOS
brew install llvm
export CXX=/usr/local/opt/llvm/bin/clang++
```

Or specify compiler:
```bash
cmake -DCMAKE_CXX_COMPILER=g++-9 ..
```

### Issue: Shared Library Not Found at Runtime

**Error**:
```
./demo: error while loading shared libraries: libqtty_ffi.so: cannot open shared object file
```

**Solution**:

The build should automatically set RPATH, but if it fails:

Linux:
```bash
export LD_LIBRARY_PATH=$PWD/../qtty/target/release:$LD_LIBRARY_PATH
./demo
```

macOS:
```bash
export DYLD_LIBRARY_PATH=$PWD/../qtty/target/release:$DYLD_LIBRARY_PATH
./demo
```

Or rebuild with explicit RPATH:
```bash
cmake -DCMAKE_BUILD_RPATH=$PWD/qtty/target/release ..
make
```

### Issue: Generated Headers Missing

**Error**:
```
fatal error: qtty/units/length.hpp: No such file or directory
```

**Solution**:

Manually run generator:
```bash
python3 gen_cpp_units.py
```

Or rebuild the generation target:
```bash
cmake --build build --target gen_cpp_units
```

Check that qtty_ffi.h exists:
```bash
ls qtty/qtty-ffi/include/qtty_ffi.h
```

If missing, build the FFI library:
```bash
cd qtty
cargo build -p qtty-ffi --release
cd ..
```

### Issue: Test Failures

**Error**:
```
Expected equality of these values:
  km.value()
    Which is: 1.0000000001
  1.0
```

**Diagnosis**:

Floating-point precision issue. Tests use `EXPECT_NEAR` with tolerance:

```cpp
EXPECT_NEAR(km.value(), 1.0, 1e-12);  // Allow 1e-12 difference
```

**Solution**:

If tests fail due to precision, check:
1. Platform differences (x86 vs ARM, 32-bit vs 64-bit)
2. Compiler optimization levels
3. Math library implementations

Adjust tolerance if necessary (but investigate root cause first).

### Issue: Google Test Download Fails

**Error**:
```
CMake Error at build/_deps/googletest-subbuild/CMakeLists.txt:
  Failed to download https://github.com/google/googletest/...
```

**Solution**:

Check internet connection. If behind proxy:
```bash
export http_proxy=http://proxy:port
export https_proxy=http://proxy:port
cmake ..
```

Or download Google Test manually and use `FetchContent_Declare` with local path.

### Issue: Build Artifacts from Previous Build

**Symptom**: Strange build errors or outdated behavior

**Solution**:

Clean build:
```bash
rm -rf build
mkdir build && cd build
cmake ..
make -j$(nproc)
```

Clean Cargo artifacts:
```bash
cd qtty
cargo clean
cd ..
rm -rf build
```

## Advanced Build Options

### Build Types

```bash
# Debug build (default)
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build (optimized)
cmake -DCMAKE_BUILD_TYPE=Release ..

# Release with debug info
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..

# Minimum size release
cmake -DCMAKE_BUILD_TYPE=MinSizeRel ..
```

### Compiler Selection

```bash
# Use Clang
cmake -DCMAKE_CXX_COMPILER=clang++ ..

# Use specific GCC version
cmake -DCMAKE_CXX_COMPILER=g++-11 ..

# Windows MSVC
cmake -G "Visual Studio 16 2019" ..
```

### Parallel Builds

```bash
# Make (Linux/macOS)
make -j$(nproc)           # Linux: use all cores
make -j$(sysctl -n hw.ncpu)  # macOS: use all cores
make -j8                  # Use 8 jobs

# CMake (cross-platform)
cmake --build . --parallel 8

# Ninja (if using Ninja generator)
ninja -j8
```

### Installation

```bash
# Install to /usr/local (requires sudo)
sudo cmake --install .

# Install to custom prefix
cmake -DCMAKE_INSTALL_PREFIX=$HOME/.local ..
cmake --build .
cmake --install .
```

Installed files:
```
<prefix>/include/qtty/
  qtty.hpp
  ffi_core.hpp
  literals.hpp
  units/*.hpp

<prefix>/include/qtty_ffi.h
```

### Verbose Build Output

```bash
# CMake verbose
cmake --build . --verbose

# Make verbose
make VERBOSE=1

# See exact commands
cmake --build . -- VERBOSE=1
```

### Custom Generator Invocation

Run generator manually with custom output:

```bash
python3 gen_cpp_units.py
```

The script looks for:
- Input: `qtty/qtty-ffi/include/qtty_ffi.h`
- Output: `include/qtty/units/*.hpp` and `include/qtty/literals.hpp`

### Using qtty-cpp in Your Project

**Method 1: CMake subdirectory** (recommended)

```cmake
# In your CMakeLists.txt
add_subdirectory(path/to/qtty-cpp)
target_link_libraries(your_target PRIVATE qtty_cpp)
```

**Method 2: CMake install + find_package**

```cmake
# After installing qtty-cpp
find_package(qtty_cpp REQUIRED)
target_link_libraries(your_target PRIVATE qtty_cpp)
```

**Method 3: Manual integration**

Copy installed headers to your include path and link against `libqtty_ffi`:

```bash
g++ -std=c++17 -I/path/to/qtty-cpp/include \
    -I/path/to/qtty-ffi/include \
    -L/path/to/qtty/target/release \
    -lqtty_ffi \
    mycode.cpp -o myapp
```

## See Also

- [Architecture Documentation](architecture.md) - Understanding the build pipeline
- [Quantity API Reference](api/quantities.md) - API details for writing tests
- [Extending Units Guide](extending-units.md) - Adding new units requires understanding build process
