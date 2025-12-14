#pragma once

#include "../ffi_core.hpp"

namespace qtty {

// Unit tags for radian-based angle units (300xx)
struct MilliradianTag {};
struct RadianTag {};

// Unit tags for degree-based angle units (310xx)
struct MicroArcsecondTag {};
struct MilliArcsecondTag {};
struct ArcsecondTag {};
struct ArcminuteTag {};
struct DegreeTag {};

// Unit tags for other angle units (320xx)
struct GradianTag {};
struct TurnTag {};
struct HourAngleTag {};

// Unit traits specializations for radian-based units
template<> struct UnitTraits<MilliradianTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MILLIRADIAN; }
};
template<> struct UnitTraits<RadianTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_RADIAN; }
};

// Unit traits specializations for degree-based units
template<> struct UnitTraits<MicroArcsecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MICRO_ARCSECOND; }
};
template<> struct UnitTraits<MilliArcsecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MILLI_ARCSECOND; }
};
template<> struct UnitTraits<ArcsecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ARCSECOND; }
};
template<> struct UnitTraits<ArcminuteTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ARCMINUTE; }
};
template<> struct UnitTraits<DegreeTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_DEGREE; }
};

// Unit traits specializations for other angle units
template<> struct UnitTraits<GradianTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_GRADIAN; }
};
template<> struct UnitTraits<TurnTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_TURN; }
};
template<> struct UnitTraits<HourAngleTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_HOUR_ANGLE; }
};

// Type aliases for convenient usage - radian-based
using Milliradian = Quantity<MilliradianTag>;
using Radian = Quantity<RadianTag>;

// Type aliases for degree-based units
using MicroArcsecond = Quantity<MicroArcsecondTag>;
using MilliArcsecond = Quantity<MilliArcsecondTag>;
using Arcsecond = Quantity<ArcsecondTag>;
using Arcminute = Quantity<ArcminuteTag>;
using Degree = Quantity<DegreeTag>;

// Type aliases for other angle units
using Gradian = Quantity<GradianTag>;
using Turn = Quantity<TurnTag>;
using HourAngle = Quantity<HourAngleTag>;

} // namespace qtty
