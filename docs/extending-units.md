# Extending Units Guide

This guide explains how to add new unit types to qtty-cpp, from modifying the Rust qtty-ffi library through generating C++ wrappers and adding tests.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Step-by-Step Guide](#step-by-step-guide)
- [Example: Adding a New Length Unit](#example-adding-a-new-length-unit)
- [Example: Adding a New Dimension](#example-adding-a-new-dimension)
- [Testing New Units](#testing-new-units)
- [Troubleshooting](#troubleshooting)

## Overview

Adding a new unit to qtty-cpp is a multi-step process that spans both the Rust qtty-ffi library and the C++ wrapper layer:

```
1. Modify Rust qtty-ffi
   - Define new unit in Rust code
   
2. Rebuild qtty-ffi
   - Generate updated qtty_ffi.h with new unit IDs
   
3. Regenerate C++ wrappers
   - Run gen_cpp_units.py to create C++ bindings
   
4. Add tests
   - Write Google Test cases for the new unit
   
5. Update documentation
   - Document the new unit in README and API docs
```

**Important**: This guide assumes you're adding units to an existing dimension (Length, Time, Angular, Mass, Power). Adding a completely new dimension requires more extensive changes.

## Prerequisites

Before adding new units, ensure you have:

- Working build environment (see [Build and Testing Guide](build-and-testing.md))
- Basic knowledge of Rust (for qtty-ffi modifications)
- Understanding of qtty-cpp architecture (see [Architecture Documentation](architecture.md))
- Familiarity with the existing test suite

## Step-by-Step Guide

### Step 1: Add Unit to Rust qtty-ffi

The qtty-ffi library is located in the `qtty/` submodule. You'll need to modify the appropriate Rust source files.

**Location**: `qtty/qtty-ffi/src/`

#### 1.1: Define the Unit Constant

Find the relevant dimension module in the qtty library (not qtty-ffi directly, as qtty-ffi depends on qtty).

For example, to add a new length unit:

**Location**: `qtty/qtty/src/dimensions/length.rs` (or similar)

Add your unit constant with appropriate conversion factor:

```rust
// Example: Adding "Chain" length unit
pub const CHAIN: Length = Length::new(20.1168);  // meters
```

The conversion factor should be the value of 1 unit expressed in the base SI unit for that dimension:
- Length: meters
- Time: seconds
- Angle: radians
- Mass: kilograms
- Power: watts

#### 1.2: Update FFI Layer

If the unit needs to be exposed through the FFI layer, add it to the unit enumeration:

**Location**: `qtty/qtty-ffi/src/unit_id.rs` (or wherever unit IDs are defined)

```rust
// Add to the appropriate enum
pub enum UnitId {
    // Existing units...
    
    #[doc = "Chain (ch)"]
    Chain = 10042,  // Choose next available discriminant in range
    
    // More units...
}
```

**Discriminant Ranges** (see [Architecture docs](architecture.md#code-generation-pipeline)):
- Length: 10000-19999
- Time: 20000-29999
- Angle: 30000-39999
- Mass: 40000-49999
- Power: 50000-59999

Choose the next available number in the appropriate range.

#### 1.3: Wire Up Conversion Logic

Ensure the conversion logic maps the unit ID to the appropriate constant:

**Location**: `qtty/qtty-ffi/src/conversions.rs` (or similar)

```rust
impl UnitId {
    pub fn to_length(&self) -> Option<Length> {
        match self {
            UnitId::Meter => Some(Length::METER),
            UnitId::Kilometer => Some(Length::KILOMETER),
            // ... existing units ...
            UnitId::Chain => Some(Length::CHAIN),  // Add your unit
            _ => None,
        }
    }
}
```

### Step 2: Rebuild qtty-ffi

After modifying the Rust code, rebuild the FFI library to generate an updated `qtty_ffi.h` header:

```bash
cd qtty
cargo build -p qtty-ffi --release
cd ..
```

This regenerates `qtty/qtty-ffi/include/qtty_ffi.h` with your new unit ID constant.

**Verify**: Check that your new unit appears in the header:

```bash
grep "UNIT_ID_CHAIN" qtty/qtty-ffi/include/qtty_ffi.h
```

Expected output:
```c
/* Chain (ch) */ UNIT_ID_CHAIN = 10042,
```

The format is critical for the C++ generator: `/* DisplayName (symbol) */ UNIT_ID_NAME = discriminant`

### Step 3: Regenerate C++ Wrappers

Run the Python generator to create C++ bindings for the new unit:

```bash
python3 gen_cpp_units.py
```

This updates:
- `include/qtty/units/length.hpp` (or appropriate dimension header)
- `include/qtty/literals.hpp`

**Verify**: Check that your unit was generated:

```bash
# Check for tag struct
grep "ChainTag" include/qtty/units/length.hpp

# Check for type alias
grep "using Chain" include/qtty/units/length.hpp

# Check for literal (if symbol is valid for C++ literal suffix)
grep "_ch" include/qtty/literals.hpp
```

Expected additions:

**Tag Struct**:
```cpp
struct ChainTag {};
```

**UnitTraits Specialization**:
```cpp
template<> struct UnitTraits<ChainTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_CHAIN; }
};
```

**Type Alias**:
```cpp
using Chain = Quantity<ChainTag>;
```

**User-Defined Literal** (if symbol is usable):
```cpp
constexpr Chain operator""_ch(long double value) {
    return Chain(static_cast<double>(value));
}
constexpr Chain operator""_ch(unsigned long long value) {
    return Chain(static_cast<double>(value));
}
```

### Step 4: Rebuild C++ Project

Rebuild the C++ project to ensure everything compiles:

```bash
cd build
cmake ..
make -j$(nproc)
```

If you encounter errors, see [Troubleshooting](#troubleshooting) below.

### Step 5: Add Tests

Add comprehensive tests for your new unit in the appropriate test file.

**Location**: `tests/test_length.cpp` (or appropriate dimension test file)

Add test cases covering:
1. Construction
2. Literal usage (if available)
3. Conversions to/from other units
4. Arithmetic operations
5. Comparisons

**Example** (adding Chain unit tests):

```cpp
TEST_F(LengthDimensionTest, ChainConstruction) {
    // Constructor
    Chain c(10.0);
    EXPECT_EQ(c.value(), 10.0);
    
    // Literal (if available)
    auto c2 = 5.0_ch;
    EXPECT_EQ(c2.value(), 5.0);
}

TEST_F(LengthDimensionTest, ChainConversions) {
    // Chain to Meter
    Chain ch(1.0);
    Meter m = ch.to<Meter>();
    EXPECT_NEAR(m.value(), 20.1168, 1e-9);
    
    // Meter to Chain
    Meter m2(20.1168);
    Chain ch2 = m2.to<Chain>();
    EXPECT_NEAR(ch2.value(), 1.0, 1e-9);
    
    // Chain to other length units
    Kilometer km = ch.to<Kilometer>();
    EXPECT_NEAR(km.value(), 0.0201168, 1e-9);
}

TEST_F(LengthDimensionTest, ChainArithmetic) {
    Chain a(10.0), b(5.0);
    
    // Addition
    Chain sum = a + b;
    EXPECT_EQ(sum.value(), 15.0);
    
    // Subtraction
    Chain diff = a - b;
    EXPECT_EQ(diff.value(), 5.0);
    
    // Scalar multiplication
    Chain doubled = a * 2.0;
    EXPECT_EQ(doubled.value(), 20.0);
    
    // Scalar division
    Chain half = a / 2.0;
    EXPECT_EQ(half.value(), 5.0);
}

TEST_F(LengthDimensionTest, ChainComparison) {
    Chain a(10.0), b(5.0), c(10.0);
    
    EXPECT_EQ(a, c);
    EXPECT_NE(a, b);
    EXPECT_GT(a, b);
    EXPECT_LT(b, a);
}
```

### Step 6: Run Tests

Rebuild and run tests to verify your new unit works correctly:

```bash
cd build
make test_ffi
./test_ffi --gtest_filter=*Chain*
```

All tests should pass.

### Step 7: Update Documentation

Update documentation to include the new unit:

#### README.md

Add the unit to the "Supported Units" section:

```markdown
### Length
- `Meter` (m)
- `Kilometer` (km)
- `Chain` (ch)  # Add this
- ...
```

#### Literals Table

If the unit has a user-defined literal, add it to the literals table in README.md and `docs/api/quantities.md`:

```markdown
| `_ch` | Chain | `20.0_ch` |
```

## Example: Adding a New Length Unit

Let's walk through a complete example: adding the "Furlong" unit (1 furlong = 201.168 meters).

### 1. Add to Rust qtty Library

**File**: `qtty/qtty/src/dimensions/length.rs`

```rust
pub const FURLONG: Length = Length::new(201.168);
```

### 2. Add FFI Unit ID

**File**: `qtty/qtty-ffi/src/unit_id.rs`

```rust
#[doc = "Furlong (fur)"]
Furlong = 10043,
```

### 3. Wire Conversion

**File**: `qtty/qtty-ffi/src/conversions.rs`

```rust
UnitId::Furlong => Some(Length::FURLONG),
```

### 4. Rebuild FFI

```bash
cd qtty
cargo build -p qtty-ffi --release
cd ..
```

### 5. Verify Header

```bash
grep Furlong qtty/qtty-ffi/include/qtty_ffi.h
```

Output:
```c
/* Furlong (fur) */ UNIT_ID_FURLONG = 10043,
```

### 6. Generate C++ Wrappers

```bash
python3 gen_cpp_units.py
```

Output:
```
Reading units from: qtty/qtty-ffi/include/qtty_ffi.h
Generated length.hpp with 58 units  # Count increased
Generated literals.hpp
...
```

### 7. Verify Generated Code

```bash
grep Furlong include/qtty/units/length.hpp
```

Output:
```cpp
struct FurlongTag {};
template<> struct UnitTraits<FurlongTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_FURLONG; }
};
using Furlong = Quantity<FurlongTag>;
```

### 8. Check Literal

```bash
grep "_fur" include/qtty/literals.hpp
```

Output:
```cpp
constexpr Furlong operator""_fur(long double value) {
    return Furlong(static_cast<double>(value));
}
constexpr Furlong operator""_fur(unsigned long long value) {
    return Furlong(static_cast<double>(value));
}
```

### 9. Add Tests

**File**: `tests/test_length.cpp`

```cpp
TEST_F(LengthDimensionTest, FurlongConversions) {
    Furlong fur(1.0);
    Meter m = fur.to<Meter>();
    EXPECT_NEAR(m.value(), 201.168, 1e-9);
    
    auto fur2 = 8.0_fur;  // 1 mile = 8 furlongs
    Mile mi = fur2.to<Mile>();
    EXPECT_NEAR(mi.value(), 1.0, 1e-6);
}
```

### 10. Build and Test

```bash
cd build
make test_ffi
./test_ffi --gtest_filter=*Furlong*
```

Output:
```
[ RUN      ] LengthDimensionTest.FurlongConversions
[       OK ] LengthDimensionTest.FurlongConversions (0 ms)
[==========] 1 test from 1 test suite ran.
[  PASSED  ] 1 test.
```

Done! The Furlong unit is now fully integrated.

## Example: Adding a New Dimension

Adding a completely new dimension (e.g., Electric Current, Temperature) requires more extensive changes:

### 1. Add Dimension to Rust qtty

**File**: `qtty/qtty/src/dimensions/mod.rs`

```rust
pub mod current;  // New dimension module
```

**File**: `qtty/qtty/src/dimensions/current.rs`

```rust
use crate::quantity::Quantity;

pub type Current = Quantity<CurrentDim>;

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct CurrentDim;

impl Current {
    pub const AMPERE: Self = Self::new(1.0);
    pub const MILLIAMPERE: Self = Self::new(0.001);
    // ... more units
}
```

### 2. Add FFI Enum Range

**File**: `qtty/qtty-ffi/src/unit_id.rs`

```rust
// Electric Current: 60000-69999
#[doc = "Ampere (A)"]
Ampere = 60000,

#[doc = "Milliampere (mA)"]
Milliampere = 60001,
```

### 3. Update Generator

**File**: `gen_cpp_units.py`

Update the dimension mapping:

```python
dimension_map = {
    1: 'Length',
    2: 'Time',
    3: 'Angle',
    4: 'Mass',
    5: 'Power',
    6: 'Current',  # Add new dimension
}
```

Add to dimension files mapping:

```python
dimension_files = {
    'Length': 'length.hpp',
    'Time': 'time.hpp',
    'Angle': 'angular.hpp',
    'Mass': 'mass.hpp',
    'Power': 'power.hpp',
    'Current': 'current.hpp',  # Add new file
}
```

### 4. Update qtty.hpp

**File**: `include/qtty/qtty.hpp`

```cpp
#include "units/current.hpp"  // Add include
```

### 5. Update Literals Header Template

**File**: `gen_cpp_units.py`

```python
LITERALS_HEADER = """#pragma once

#include "units/length.hpp"
#include "units/time.hpp"
#include "units/angular.hpp"
#include "units/mass.hpp"
#include "units/power.hpp"
#include "units/current.hpp"  // Add include

namespace qtty {
// ...
```

### 6. Add Test Suite

**File**: `tests/test_current.cpp`

```cpp
#include "fixtures.hpp"

TEST_F(CurrentDimensionTest, AmpereConstruction) {
    Ampere a(10.0);
    EXPECT_EQ(a.value(), 10.0);
}

TEST_F(CurrentDimensionTest, CurrentConversions) {
    Ampere a(1.0);
    Milliampere ma = a.to<Milliampere>();
    EXPECT_NEAR(ma.value(), 1000.0, 1e-9);
}
```

### 7. Update CMakeLists.txt

**File**: `CMakeLists.txt`

Add to generated headers list:

```cmake
set(GENERATED_HEADERS
    # ... existing headers ...
    ${CMAKE_CURRENT_SOURCE_DIR}/include/qtty/units/current.hpp
)
```

Add test file to test sources:

```cmake
set(TEST_FFI_SOURCES
    # ... existing sources ...
    tests/test_current.cpp
)
```

### 8. Update Fixtures

**File**: `tests/fixtures.hpp`

```cpp
class CurrentDimensionTest : public QttyTest {};
```

## Testing New Units

### Recommended Test Coverage

For each new unit, add tests covering:

1. **Construction**
   - Constructor with value
   - User-defined literal (if available)
   - Default constructor (value should be 0.0)

2. **Conversions**
   - To base unit (e.g., Chain -> Meter)
   - From base unit (e.g., Meter -> Chain)
   - To other units in same dimension
   - Round-trip conversion (A -> B -> A)

3. **Arithmetic**
   - Addition with same unit
   - Subtraction with same unit
   - Scalar multiplication
   - Scalar division
   - Compound assignment (+=, -=, *=, /=)

4. **Comparisons**
   - Equality (==, !=)
   - Ordering (<, >, <=, >=)

5. **Utilities**
   - Absolute value
   - Negation

6. **Edge Cases**
   - Very small values
   - Very large values
   - Zero
   - Negative values

### Test Template

Use this template for new unit tests:

```cpp
TEST_F(DimensionNameTest, UnitNameConstruction) {
    // Constructor
    UnitName u(10.0);
    EXPECT_EQ(u.value(), 10.0);
    
    // Literal (if available)
    auto u2 = 5.0_suffix;
    EXPECT_EQ(u2.value(), 5.0);
    
    // Default constructor
    UnitName u3;
    EXPECT_EQ(u3.value(), 0.0);
}

TEST_F(DimensionNameTest, UnitNameConversions) {
    // To base unit
    UnitName u(1.0);
    BaseUnit base = u.to<BaseUnit>();
    EXPECT_NEAR(base.value(), CONVERSION_FACTOR, TOLERANCE);
    
    // From base unit
    BaseUnit base2(CONVERSION_FACTOR);
    UnitName u2 = base2.to<UnitName>();
    EXPECT_NEAR(u2.value(), 1.0, TOLERANCE);
    
    // Round-trip
    UnitName u3(42.0);
    BaseUnit base3 = u3.to<BaseUnit>();
    UnitName u4 = base3.to<UnitName>();
    EXPECT_NEAR(u4.value(), 42.0, TOLERANCE);
}

TEST_F(DimensionNameTest, UnitNameArithmetic) {
    UnitName a(10.0), b(3.0);
    
    EXPECT_EQ((a + b).value(), 13.0);
    EXPECT_EQ((a - b).value(), 7.0);
    EXPECT_EQ((a * 2.0).value(), 20.0);
    EXPECT_EQ((a / 2.0).value(), 5.0);
}

TEST_F(DimensionNameTest, UnitNameComparison) {
    UnitName a(10.0), b(5.0), c(10.0);
    
    EXPECT_EQ(a, c);
    EXPECT_NE(a, b);
    EXPECT_GT(a, b);
    EXPECT_LT(b, a);
    EXPECT_GE(a, c);
    EXPECT_LE(b, a);
}

TEST_F(DimensionNameTest, UnitNameUtilities) {
    UnitName neg(-10.5);
    EXPECT_EQ(neg.abs().value(), 10.5);
    EXPECT_EQ((-neg).value(), 10.5);
}
```

## Troubleshooting

### Issue: Unit Not Generated

**Symptom**: After running `gen_cpp_units.py`, your unit doesn't appear in the generated headers.

**Diagnosis**:

Check the generator output for warnings:
```bash
python3 gen_cpp_units.py
```

Common causes:

1. **Comment format incorrect in qtty_ffi.h**

   Must be exactly: `/* DisplayName (symbol) */ UNIT_ID_NAME = discriminant,`

   Check:
   ```bash
   grep "UNIT_ID_YOURUNIT" qtty/qtty-ffi/include/qtty_ffi.h
   ```

2. **Discriminant outside recognized range**

   Discriminants must be in defined ranges (10000-59999).

3. **FFI header not regenerated**

   Rebuild qtty-ffi:
   ```bash
   cd qtty
   cargo build -p qtty-ffi --release
   cd ..
   ```

### Issue: Literal Suffix Collision

**Symptom**: Generator warning about skipping literal.

**Example**:
```
Warning: Skipping literal _nm for NauticalMile (conflicts with Nanometer)
```

**Solution**:

The generator automatically skips conflicting literals. Users can still use the constructor:

```cpp
NauticalMile nm(10.0);  // OK
// auto nm = 10.0_nm;   // Would be ambiguous
```

To add a unique literal manually:

**File**: `include/qtty/literals.hpp`

```cpp
// Add after generated literals
constexpr NauticalMile operator""_nmi(long double value) {
    return NauticalMile(static_cast<double>(value));
}
constexpr NauticalMile operator""_nmi(unsigned long long value) {
    return NauticalMile(static_cast<double>(value));
}
```

### Issue: Conversion Factor Incorrect

**Symptom**: Tests fail with unexpected conversion values.

**Example**:
```
Expected: 1.0
Actual: 1.09361
```

**Diagnosis**:

The conversion factor in the Rust code is incorrect.

**Solution**:

1. Verify the conversion factor (1 of your unit = ? base units)
2. Update the Rust constant
3. Rebuild qtty-ffi
4. Regenerate C++ headers
5. Rerun tests

### Issue: Compile Errors After Adding Unit

**Symptom**: Build fails with template errors.

**Common Errors**:

1. **Missing include in qtty.hpp**

   Add your dimension header:
   ```cpp
   #include "units/your_dimension.hpp"
   ```

2. **Missing UnitTraits specialization**

   Should be auto-generated. Verify:
   ```bash
   grep "UnitTraits<YourUnitTag>" include/qtty/units/*.hpp
   ```

3. **Mismatched tag names**

   Tag struct name must match usage:
   ```cpp
   struct MeterTag {};  // Tag struct
   using Meter = Quantity<MeterTag>;  // Must use same name
   ```

### Issue: Tests Not Running

**Symptom**: `ctest` or `./test_ffi` doesn't run your new tests.

**Solution**:

1. Ensure test file is added to CMakeLists.txt:

   ```cmake
   set(TEST_FFI_SOURCES
       tests/main.cpp
       tests/fixtures.hpp
       tests/test_your_dimension.cpp  # Add this
       # ...
   )
   ```

2. Rebuild test executable:

   ```bash
   cd build
   make test_ffi
   ```

3. Verify tests are discovered:

   ```bash
   ./test_ffi --gtest_list_tests | grep YourTest
   ```

## See Also

- [Architecture Documentation](architecture.md) - Understanding the generation pipeline
- [Build and Testing Guide](build-and-testing.md) - Building and testing
- [Quantity API Reference](api/quantities.md) - API details for new units
- [qtty Rust Documentation](https://docs.rs/qtty) - Rust library documentation
