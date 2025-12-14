#pragma once

#include "../ffi_core.hpp"
#include "length_ffi.hpp"
#include "time_ffi.hpp"

namespace qtty {

// Template for compound units (e.g., velocity = length/time)
template<typename NumeratorTag, typename DenominatorTag>
struct CompoundTag {};

// Velocity type alias using compound units
template<typename LengthUnit, typename TimeUnit>
using Velocity = Quantity<CompoundTag<typename LengthUnit::unit_tag, typename TimeUnit::unit_tag>>;

// Note: The C API doesn't have explicit velocity unit IDs
// We create velocity by dividing length by time, operating on raw values
// No unit conversion is available for compound units through the C API

// Division operator to create velocity from length and time
template<typename LengthTag, typename TimeTag>
Quantity<CompoundTag<LengthTag, TimeTag>> operator/(
    const Quantity<LengthTag>& length,
    const Quantity<TimeTag>& time)
{
    return Quantity<CompoundTag<LengthTag, TimeTag>>(length.value() / time.value());
}

// Common velocity type aliases (constructed from division, not convertible)
using MeterPerSecond = Quantity<CompoundTag<MeterTag, SecondTag>>;
using KilometerPerHour = Quantity<CompoundTag<KilometerTag, HourTag>>;

} // namespace qtty
