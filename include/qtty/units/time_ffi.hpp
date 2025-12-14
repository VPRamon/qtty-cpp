#pragma once

#include "../ffi_core.hpp"

namespace qtty {

// Unit tags for time units
struct SecondTag {};
struct MinuteTag {};
struct HourTag {};
struct DayTag {};

// Unit traits specializations for time units
template<>
struct UnitTraits<SecondTag> {
    static constexpr UnitId unit_id() {
        return UNIT_ID_SECOND;
    }
};

template<>
struct UnitTraits<MinuteTag> {
    static constexpr UnitId unit_id() {
        return UNIT_ID_MINUTE;
    }
};

template<>
struct UnitTraits<HourTag> {
    static constexpr UnitId unit_id() {
        return UNIT_ID_HOUR;
    }
};

template<>
struct UnitTraits<DayTag> {
    static constexpr UnitId unit_id() {
        return UNIT_ID_DAY;
    }
};

// Type aliases for convenient usage
using Second = Quantity<SecondTag>;
using Minute = Quantity<MinuteTag>;
using Hour = Quantity<HourTag>;
using Day = Quantity<DayTag>;

} // namespace qtty
