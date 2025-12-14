#pragma once

#include "../ffi_core.hpp"

namespace qtty {

// Unit tags for mass units (SI metric - 400xx)
struct YoctogramTag {};
struct ZeptogramTag {};
struct AttogramTag {};
struct FemtogramTag {};
struct PicogramTag {};
struct NanogramTag {};
struct MicrogramTag {};
struct MilligramTag {};
struct CentigramTag {};
struct DecigramTag {};
struct GramTag {};
struct DecagramTag {};
struct HectogramTag {};
struct KilogramTag {};
struct MegagramTag {};
struct GigagramTag {};
struct TeragramTag {};
struct PetagramTag {};
struct ExagramTag {};
struct ZettagramTag {};
struct YottagramTag {};

// Imperial mass units (410xx)
struct GrainTag {};
struct OunceTag {};
struct PoundTag {};
struct StoneTag {};
struct ShortTonTag {};
struct LongTonTag {};

// Special mass units (420xx)
struct CaratTag {};
struct TonneTag {};
struct AtomicMassUnitTag {};
struct SolarMassTag {};

// Unit traits specializations for SI metric mass units
template<> struct UnitTraits<YoctogramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_YOCTOGRAM; }
};
template<> struct UnitTraits<ZeptogramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ZEPTOGRAM; }
};
template<> struct UnitTraits<AttogramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ATTOGRAM; }
};
template<> struct UnitTraits<FemtogramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_FEMTOGRAM; }
};
template<> struct UnitTraits<PicogramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_PICOGRAM; }
};
template<> struct UnitTraits<NanogramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NANOGRAM; }
};
template<> struct UnitTraits<MicrogramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MICROGRAM; }
};
template<> struct UnitTraits<MilligramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MILLIGRAM; }
};
template<> struct UnitTraits<CentigramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_CENTIGRAM; }
};
template<> struct UnitTraits<DecigramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_DECIGRAM; }
};
template<> struct UnitTraits<GramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_GRAM; }
};
template<> struct UnitTraits<DecagramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_DECAGRAM; }
};
template<> struct UnitTraits<HectogramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_HECTOGRAM; }
};
template<> struct UnitTraits<KilogramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_KILOGRAM; }
};
template<> struct UnitTraits<MegagramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MEGAGRAM; }
};
template<> struct UnitTraits<GigagramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_GIGAGRAM; }
};
template<> struct UnitTraits<TeragramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_TERAGRAM; }
};
template<> struct UnitTraits<PetagramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_PETAGRAM; }
};
template<> struct UnitTraits<ExagramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_EXAGRAM; }
};
template<> struct UnitTraits<ZettagramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ZETTAGRAM; }
};
template<> struct UnitTraits<YottagramTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_YOTTAGRAM; }
};

// Unit traits specializations for Imperial mass units
template<> struct UnitTraits<GrainTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_GRAIN; }
};
template<> struct UnitTraits<OunceTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_OUNCE; }
};
template<> struct UnitTraits<PoundTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_POUND; }
};
template<> struct UnitTraits<StoneTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_STONE; }
};
template<> struct UnitTraits<ShortTonTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_SHORT_TON; }
};
template<> struct UnitTraits<LongTonTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_LONG_TON; }
};

// Unit traits specializations for Special mass units
template<> struct UnitTraits<CaratTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_CARAT; }
};
template<> struct UnitTraits<TonneTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_TONNE; }
};
template<> struct UnitTraits<AtomicMassUnitTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ATOMIC_MASS_UNIT; }
};
template<> struct UnitTraits<SolarMassTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_SOLAR_MASS; }
};

// Type aliases for convenient usage - SI metric
using Yoctogram = Quantity<YoctogramTag>;
using Zeptogram = Quantity<ZeptogramTag>;
using Attogram = Quantity<AttogramTag>;
using Femtogram = Quantity<FemtogramTag>;
using Picogram = Quantity<PicogramTag>;
using Nanogram = Quantity<NanogramTag>;
using Microgram = Quantity<MicrogramTag>;
using Milligram = Quantity<MilligramTag>;
using Centigram = Quantity<CentigramTag>;
using Decigram = Quantity<DecigramTag>;
using Gram = Quantity<GramTag>;
using Decagram = Quantity<DecagramTag>;
using Hectogram = Quantity<HectogramTag>;
using Kilogram = Quantity<KilogramTag>;
using Megagram = Quantity<MegagramTag>;
using Gigagram = Quantity<GigagramTag>;
using Teragram = Quantity<TeragramTag>;
using Petagram = Quantity<PetagramTag>;
using Exagram = Quantity<ExagramTag>;
using Zettagram = Quantity<ZettagramTag>;
using Yottagram = Quantity<YottagramTag>;

// Type aliases for Imperial units
using Grain = Quantity<GrainTag>;
using Ounce = Quantity<OunceTag>;
using Pound = Quantity<PoundTag>;
using Stone = Quantity<StoneTag>;
using ShortTon = Quantity<ShortTonTag>;
using LongTon = Quantity<LongTonTag>;

// Type aliases for Special units
using Carat = Quantity<CaratTag>;
using Tonne = Quantity<TonneTag>;
using AtomicMassUnit = Quantity<AtomicMassUnitTag>;
using SolarMass = Quantity<SolarMassTag>;

} // namespace qtty
