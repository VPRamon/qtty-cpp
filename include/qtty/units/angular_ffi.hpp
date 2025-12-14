#pragma once

#include "../ffi_core.hpp"

namespace qtty {

// Unit tags for angular units
struct RadianTag {};
struct DegreeTag {};

// Unit traits specializations for angular units
template<>
struct UnitTraits<RadianTag> {
    static constexpr UnitId unit_id() {
        return UNIT_ID_RADIAN;
    }
};

template<>
struct UnitTraits<DegreeTag> {
    static constexpr UnitId unit_id() {
        return UNIT_ID_DEGREE;
    }
};

// Type aliases for convenient usage
using Radian = Quantity<RadianTag>;
using Degree = Quantity<DegreeTag>;

} // namespace qtty
