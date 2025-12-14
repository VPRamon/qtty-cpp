#pragma once

#include "../ffi_core.hpp"

namespace qtty {

// Unit tags for power units (SI metric - 500xx)
struct YoctowattTag {};
struct ZeptowattTag {};
struct AttowattTag {};
struct FemtowattTag {};
struct PicowattTag {};
struct NanowattTag {};
struct MicrowattTag {};
struct MilliwattTag {};
struct DeciwattTag {};
struct WattTag {};
struct DecawattTag {};
struct HectowattTag {};
struct KilowattTag {};
struct MegawattTag {};
struct GigawattTag {};
struct TerawattTag {};
struct PetawattTag {};
struct ExawattTag {};
struct ZettawattTag {};
struct YottawattTag {};

// Other power units (510xx)
struct ErgPerSecondTag {};
struct HorsepowerMetricTag {};
struct HorsepowerElectricTag {};
struct SolarLuminosityTag {};

// Unit traits specializations for SI metric power units
template<> struct UnitTraits<YoctowattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_YOCTOWATT; }
};
template<> struct UnitTraits<ZeptowattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ZEPTOWATT; }
};
template<> struct UnitTraits<AttowattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ATTOWATT; }
};
template<> struct UnitTraits<FemtowattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_FEMTOWATT; }
};
template<> struct UnitTraits<PicowattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_PICOWATT; }
};
template<> struct UnitTraits<NanowattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NANOWATT; }
};
template<> struct UnitTraits<MicrowattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MICROWATT; }
};
template<> struct UnitTraits<MilliwattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MILLIWATT; }
};
template<> struct UnitTraits<DeciwattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_DECIWATT; }
};
template<> struct UnitTraits<WattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_WATT; }
};
template<> struct UnitTraits<DecawattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_DECAWATT; }
};
template<> struct UnitTraits<HectowattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_HECTOWATT; }
};
template<> struct UnitTraits<KilowattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_KILOWATT; }
};
template<> struct UnitTraits<MegawattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MEGAWATT; }
};
template<> struct UnitTraits<GigawattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_GIGAWATT; }
};
template<> struct UnitTraits<TerawattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_TERAWATT; }
};
template<> struct UnitTraits<PetawattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_PETAWATT; }
};
template<> struct UnitTraits<ExawattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_EXAWATT; }
};
template<> struct UnitTraits<ZettawattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ZETTAWATT; }
};
template<> struct UnitTraits<YottawattTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_YOTTAWATT; }
};

// Unit traits specializations for other power units
template<> struct UnitTraits<ErgPerSecondTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ERG_PER_SECOND; }
};
template<> struct UnitTraits<HorsepowerMetricTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_HORSEPOWER_METRIC; }
};
template<> struct UnitTraits<HorsepowerElectricTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_HORSEPOWER_ELECTRIC; }
};
template<> struct UnitTraits<SolarLuminosityTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_SOLAR_LUMINOSITY; }
};

// Type aliases for convenient usage - SI metric
using Yoctowatt = Quantity<YoctowattTag>;
using Zeptowatt = Quantity<ZeptowattTag>;
using Attowatt = Quantity<AttowattTag>;
using Femtowatt = Quantity<FemtowattTag>;
using Picowatt = Quantity<PicowattTag>;
using Nanowatt = Quantity<NanowattTag>;
using Microwatt = Quantity<MicrowattTag>;
using Milliwatt = Quantity<MilliwattTag>;
using Deciwatt = Quantity<DeciwattTag>;
using Watt = Quantity<WattTag>;
using Decawatt = Quantity<DecawattTag>;
using Hectowatt = Quantity<HectowattTag>;
using Kilowatt = Quantity<KilowattTag>;
using Megawatt = Quantity<MegawattTag>;
using Gigawatt = Quantity<GigawattTag>;
using Terawatt = Quantity<TerawattTag>;
using Petawatt = Quantity<PetawattTag>;
using Exawatt = Quantity<ExawattTag>;
using Zettawatt = Quantity<ZettawattTag>;
using Yottawatt = Quantity<YottawattTag>;

// Type aliases for other units
using ErgPerSecond = Quantity<ErgPerSecondTag>;
using HorsepowerMetric = Quantity<HorsepowerMetricTag>;
using HorsepowerElectric = Quantity<HorsepowerElectricTag>;
using SolarLuminosity = Quantity<SolarLuminosityTag>;

} // namespace qtty
