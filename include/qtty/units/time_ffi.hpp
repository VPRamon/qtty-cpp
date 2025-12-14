#pragma once

#include "../ffi_core.hpp"

namespace qtty {

// Unit tags for SI metric time units (200xx)
struct AttosecondTag {};
struct FemtosecondTag {};
struct PicosecondTag {};
struct NanosecondTag {};
struct MicrosecondTag {};
struct MillisecondTag {};
struct CentisecondTag {};
struct DecisecondTag {};
struct SecondTag {};
struct DecasecondTag {};
struct HectosecondTag {};
struct KilosecondTag {};
struct MegasecondTag {};
struct GigasecondTag {};
struct TerasecondTag {};

// Common time units (210xx)
struct MinuteTag {};
struct HourTag {};
struct DayTag {};
struct WeekTag {};
struct FortnightTag {};

// Calendar time units (220xx)
struct YearTag {};
struct DecadeTag {};
struct CenturyTag {};
struct MillenniumTag {};
struct JulianYearTag {};
struct JulianCenturyTag {};

// Astronomical time units (230xx)
struct SiderealDayTag {};
struct SynodicMonthTag {};
struct SiderealYearTag {};

// Unit traits specializations for SI metric time units
template<> struct UnitTraits<AttosecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ATTOSECOND; }
};
template<> struct UnitTraits<FemtosecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_FEMTOSECOND; }
};
template<> struct UnitTraits<PicosecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_PICOSECOND; }
};
template<> struct UnitTraits<NanosecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NANOSECOND; }
};
template<> struct UnitTraits<MicrosecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MICROSECOND; }
};
template<> struct UnitTraits<MillisecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MILLISECOND; }
};
template<> struct UnitTraits<CentisecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_CENTISECOND; }
};
template<> struct UnitTraits<DecisecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_DECISECOND; }
};
template<> struct UnitTraits<SecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_SECOND; }
};
template<> struct UnitTraits<DecasecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_DECASECOND; }
};
template<> struct UnitTraits<HectosecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_HECTOSECOND; }
};
template<> struct UnitTraits<KilosecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_KILOSECOND; }
};
template<> struct UnitTraits<MegasecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MEGASECOND; }
};
template<> struct UnitTraits<GigasecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_GIGASECOND; }
};
template<> struct UnitTraits<TerasecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_TERASECOND; }
};

// Unit traits specializations for common time units
template<> struct UnitTraits<MinuteTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MINUTE; }
};
template<> struct UnitTraits<HourTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_HOUR; }
};
template<> struct UnitTraits<DayTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_DAY; }
};
template<> struct UnitTraits<WeekTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_WEEK; }
};
template<> struct UnitTraits<FortnightTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_FORTNIGHT; }
};

// Unit traits specializations for calendar time units
template<> struct UnitTraits<YearTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_YEAR; }
};
template<> struct UnitTraits<DecadeTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_DECADE; }
};
template<> struct UnitTraits<CenturyTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_CENTURY; }
};
template<> struct UnitTraits<MillenniumTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MILLENNIUM; }
};
template<> struct UnitTraits<JulianYearTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_JULIAN_YEAR; }
};
template<> struct UnitTraits<JulianCenturyTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_JULIAN_CENTURY; }
};

// Unit traits specializations for astronomical time units
template<> struct UnitTraits<SiderealDayTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_SIDEREAL_DAY; }
};
template<> struct UnitTraits<SynodicMonthTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_SYNODIC_MONTH; }
};
template<> struct UnitTraits<SiderealYearTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_SIDEREAL_YEAR; }
};

// Type aliases for convenient usage - SI metric
using Attosecond = Quantity<AttosecondTag>;
using Femtosecond = Quantity<FemtosecondTag>;
using Picosecond = Quantity<PicosecondTag>;
using Nanosecond = Quantity<NanosecondTag>;
using Microsecond = Quantity<MicrosecondTag>;
using Millisecond = Quantity<MillisecondTag>;
using Centisecond = Quantity<CentisecondTag>;
using Decisecond = Quantity<DecisecondTag>;
using Second = Quantity<SecondTag>;
using Decasecond = Quantity<DecasecondTag>;
using Hectosecond = Quantity<HectosecondTag>;
using Kilosecond = Quantity<KilosecondTag>;
using Megasecond = Quantity<MegasecondTag>;
using Gigasecond = Quantity<GigasecondTag>;
using Terasecond = Quantity<TerasecondTag>;

// Type aliases for common time units
using Minute = Quantity<MinuteTag>;
using Hour = Quantity<HourTag>;
using Day = Quantity<DayTag>;
using Week = Quantity<WeekTag>;
using Fortnight = Quantity<FortnightTag>;

// Type aliases for calendar time units
using Year = Quantity<YearTag>;
using Decade = Quantity<DecadeTag>;
using Century = Quantity<CenturyTag>;
using Millennium = Quantity<MillenniumTag>;
using JulianYear = Quantity<JulianYearTag>;
using JulianCentury = Quantity<JulianCenturyTag>;

// Type aliases for astronomical time units
using SiderealDay = Quantity<SiderealDayTag>;
using SynodicMonth = Quantity<SynodicMonthTag>;
using SiderealYear = Quantity<SiderealYearTag>;

} // namespace qtty
