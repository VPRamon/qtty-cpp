#pragma once

#include "../ffi_core.hpp"

namespace qtty {

// Unit tags for length units
struct MeterTag {};
struct KilometerTag {};

// Unit traits specializations for length units
template<>
struct UnitTraits<MeterTag> {
    static constexpr UnitId unit_id() {
        return UNIT_ID_METER;
    }
};

template<>
struct UnitTraits<KilometerTag> {
    static constexpr UnitId unit_id() {
        return UNIT_ID_KILOMETER;
    }
};

// Type aliases for convenient usage
using Meter = Quantity<MeterTag>;
using Kilometer = Quantity<KilometerTag>;

} // namespace qtty
