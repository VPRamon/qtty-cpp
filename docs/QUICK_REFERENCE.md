# qtty-cpp Quick Reference

One-page reference for common tasks.

## Include

```cpp
#include "qtty/qtty.hpp"
using namespace qtty;
```

## Create Quantities

```cpp
// Constructor
Meter m(10.0);
Second s(5.0);

// User-defined literal
auto distance = 100.0_km;
auto time = 2.0_h;
```

## Convert Units

```cpp
Meter m(1000.0);
Kilometer km = m.to<Kilometer>();  // 1.0 km

// Or with auto
auto km = m.to<Kilometer>();
```

## Arithmetic

```cpp
Meter a(10.0), b(5.0);

auto sum = a + b;      // 15 m
auto diff = a - b;     // 5 m
auto scaled = a * 2.0; // 20 m
auto half = a / 2.0;   // 5 m

// Compound assignment
a += 5.0_m;
a *= 2.0;
```

## Comparisons

```cpp
Meter a(10.0), b(5.0);

if (a > b) { /* ... */ }
if (a == b) { /* ... */ }

// Works with standard algorithms
std::vector<Meter> distances = {10.0_m, 5.0_m, 15.0_m};
std::sort(distances.begin(), distances.end());
```

## Compound Units (Velocity)

```cpp
Meter distance(100.0);
Second time(20.0);

auto velocity = distance / time;  // Type: MeterPerSecond
std::cout << velocity.value();    // Prints: 5.0
```

## Error Handling

```cpp
try {
    Meter m(100.0);
    Second s = m.to<Second>();  // Incompatible dimensions
} catch (const IncompatibleDimensionsError& e) {
    std::cerr << e.what() << '\n';
}
```

## Common Units

### Length
`Meter`, `Kilometer`, `Millimeter`, `Centimeter`, `Inch`, `Foot`, `Mile`, `LightYear`

Literals: `_m`, `_km`, `_mm`, `_cm`, `_in`, `_ft`, `_mi`, `_ly`

### Time
`Second`, `Minute`, `Hour`, `Day`, `Millisecond`, `Microsecond`

Literals: `_s`, `_min`, `_h`, `_day`, `_ms`, `_us`

### Angular
`Radian`, `Degree`, `Arcminute`, `Arcsecond`

Literals: `_rad`, `_deg`, `_arcmin`, `_arcsec`

### Mass
`Kilogram`, `Gram`, `Milligram`, `Ton`, `Pound`, `Ounce`

Literals: `_kg`, `_g`, `_mg`, `_ton`, `_lb`, `_oz`

### Power
`Watt`, `Kilowatt`, `Megawatt`, `Horsepower`

Literals: `_W`, `_kW`, `_MW`, `_hp`

## Building

```bash
# Clone with submodules
git clone --recurse-submodules <repo-url>
cd qtty-cpp

# Build
cmake -S . -B build
cmake --build build --parallel

# Test
ctest --test-dir build --output-on-failure
```

## CMake Integration

```cmake
# In your CMakeLists.txt
add_subdirectory(path/to/qtty-cpp)
target_link_libraries(your_target PRIVATE qtty_cpp)
```

## Documentation

- [README](../README.md) - Overview and quick start
- [Architecture](architecture.md) - Design details
- [API Reference](api/quantities.md) - Complete API
- [Build Guide](build-and-testing.md) - Build and test
- [Extending](extending-units.md) - Add new units

## Common Operations

| Operation | Code | Result Type |
|-----------|------|-------------|
| Create | `Meter m(10.0)` | `Meter` |
| Literal | `auto m = 10.0_m` | `Meter` |
| Convert | `m.to<Kilometer>()` | `Kilometer` |
| Add | `a + b` | Same unit |
| Multiply | `m * 2.0` | Same unit |
| Divide | `m / 2.0` | Same unit |
| Compare | `a > b` | `bool` |
| Get value | `m.value()` | `double` |
| Absolute | `m.abs()` | Same unit |
| Negate | `-m` | Same unit |

## Type Safety

```cpp
Meter m(10.0);
Second s(5.0);

// OK: Same unit
auto sum = m + m;

// Compile error: different types
// auto bad = m + s;

// Convert to a compatible unit first
Kilometer km = m.to<Kilometer>();
auto sum2 = m + km.to<Meter>();

// Runtime error: incompatible dimensions
// Second s2 = m.to<Second>();  // Throws IncompatibleDimensionsError
```

## Exception Types

| Exception | When Thrown |
|-----------|-------------|
| `InvalidUnitError` | Unknown unit ID |
| `IncompatibleDimensionsError` | Converting incompatible dimensions |
| `ConversionError` | Invalid numeric value |
| `QttyException` | Base class (catch-all) |

## Troubleshooting

| Problem | Solution |
|---------|----------|
| Submodule missing | `git submodule update --init --recursive` |
| Library not found | Check RPATH or set `LD_LIBRARY_PATH` |
| Generated headers missing | Run `python3 gen_cpp_units.py` |
| Python not found | Install Python 3.6+ or set `Python3_EXECUTABLE` |
| Cargo not found | Install Rust: `curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs \| sh` |

---

See `docs/README.md` for additional documentation.
