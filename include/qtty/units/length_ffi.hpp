#pragma once

#include "../ffi_core.hpp"

namespace qtty {

// Unit tags for SI metric length units (100xx)
struct PlanckLengthTag {};
struct YoctometerTag {};
struct ZeptometerTag {};
struct AttometerTag {};
struct FemtometerTag {};
struct PicometerTag {};
struct NanometerTag {};
struct MicrometerTag {};
struct MillimeterTag {};
struct CentimeterTag {};
struct DecimeterTag {};
struct MeterTag {};
struct DecameterTag {};
struct HectometerTag {};
struct KilometerTag {};
struct MegameterTag {};
struct GigameterTag {};
struct TerameterTag {};
struct PetameterTag {};
struct ExameterTag {};
struct ZettameterTag {};
struct YottameterTag {};

// Astronomical length units (110xx)
struct BohrRadiusTag {};
struct ClassicalElectronRadiusTag {};
struct ElectronReducedComptonWavelengthTag {};
struct AstronomicalUnitTag {};
struct LightYearTag {};
struct ParsecTag {};
struct KiloparsecTag {};
struct MegaparsecTag {};
struct GigaparsecTag {};

// Imperial length units (120xx)
struct InchTag {};
struct FootTag {};
struct YardTag {};
struct MileTag {};

// Nautical length units (130xx)
struct LinkTag {};
struct FathomTag {};
struct RodTag {};
struct ChainTag {};
struct NauticalMileTag {};

// Nominal length units (150xx)
struct NominalLunarRadiusTag {};
struct NominalLunarDistanceTag {};
struct NominalEarthPolarRadiusTag {};
struct NominalEarthRadiusTag {};
struct NominalEarthEquatorialRadiusTag {};
struct EarthMeridionalCircumferenceTag {};
struct EarthEquatorialCircumferenceTag {};
struct NominalJupiterRadiusTag {};
struct NominalSolarRadiusTag {};
struct NominalSolarDiameterTag {};

// Unit traits specializations for SI metric length units
template<> struct UnitTraits<PlanckLengthTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_PLANCK_LENGTH; }
};
template<> struct UnitTraits<YoctometerTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_YOCTOMETER; }
};
template<> struct UnitTraits<ZeptometerTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ZEPTOMETER; }
};
template<> struct UnitTraits<AttometerTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ATTOMETER; }
};
template<> struct UnitTraits<FemtometerTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_FEMTOMETER; }
};
template<> struct UnitTraits<PicometerTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_PICOMETER; }
};
template<> struct UnitTraits<NanometerTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NANOMETER; }
};
template<> struct UnitTraits<MicrometerTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MICROMETER; }
};
template<> struct UnitTraits<MillimeterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MILLIMETER; }
};
template<> struct UnitTraits<CentimeterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_CENTIMETER; }
};
template<> struct UnitTraits<DecimeterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_DECIMETER; }
};
template<> struct UnitTraits<MeterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_METER; }
};
template<> struct UnitTraits<DecameterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_DECAMETER; }
};
template<> struct UnitTraits<HectometerTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_HECTOMETER; }
};
template<> struct UnitTraits<KilometerTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_KILOMETER; }
};
template<> struct UnitTraits<MegameterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MEGAMETER; }
};
template<> struct UnitTraits<GigameterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_GIGAMETER; }
};
template<> struct UnitTraits<TerameterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_TERAMETER; }
};
template<> struct UnitTraits<PetameterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_PETAMETER; }
};
template<> struct UnitTraits<ExameterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_EXAMETER; }
};
template<> struct UnitTraits<ZettameterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ZETTAMETER; }
};
template<> struct UnitTraits<YottameterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_YOTTAMETER; }
};

// Unit traits specializations for astronomical length units
template<> struct UnitTraits<BohrRadiusTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_BOHR_RADIUS; }
};
template<> struct UnitTraits<ClassicalElectronRadiusTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_CLASSICAL_ELECTRON_RADIUS; }
};
template<> struct UnitTraits<ElectronReducedComptonWavelengthTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ELECTRON_REDUCED_COMPTON_WAVELENGTH; }
};
template<> struct UnitTraits<AstronomicalUnitTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ASTRONOMICAL_UNIT; }
};
template<> struct UnitTraits<LightYearTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_LIGHT_YEAR; }
};
template<> struct UnitTraits<ParsecTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_PARSEC; }
};
template<> struct UnitTraits<KiloparsecTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_KILOPARSEC; }
};
template<> struct UnitTraits<MegaparsecTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MEGAPARSEC; }
};
template<> struct UnitTraits<GigaparsecTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_GIGAPARSEC; }
};

// Unit traits specializations for imperial length units
template<> struct UnitTraits<InchTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_INCH; }
};
template<> struct UnitTraits<FootTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_FOOT; }
};
template<> struct UnitTraits<YardTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_YARD; }
};
template<> struct UnitTraits<MileTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_MILE; }
};

// Unit traits specializations for nautical length units
template<> struct UnitTraits<LinkTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_LINK; }
};
template<> struct UnitTraits<FathomTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_FATHOM; }
};
template<> struct UnitTraits<RodTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_ROD; }
};
template<> struct UnitTraits<ChainTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_CHAIN; }
};
template<> struct UnitTraits<NauticalMileTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NAUTICAL_MILE; }
};

// Unit traits specializations for nominal length units
template<> struct UnitTraits<NominalLunarRadiusTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NOMINAL_LUNAR_RADIUS; }
};
template<> struct UnitTraits<NominalLunarDistanceTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NOMINAL_LUNAR_DISTANCE; }
};
template<> struct UnitTraits<NominalEarthPolarRadiusTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NOMINAL_EARTH_POLAR_RADIUS; }
};
template<> struct UnitTraits<NominalEarthRadiusTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NOMINAL_EARTH_RADIUS; }
};
template<> struct UnitTraits<NominalEarthEquatorialRadiusTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NOMINAL_EARTH_EQUATORIAL_RADIUS; }
};
template<> struct UnitTraits<EarthMeridionalCircumferenceTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_EARTH_MERIDIONAL_CIRCUMFERENCE; }
};
template<> struct UnitTraits<EarthEquatorialCircumferenceTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_EARTH_EQUATORIAL_CIRCUMFERENCE; }
};
template<> struct UnitTraits<NominalJupiterRadiusTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NOMINAL_JUPITER_RADIUS; }
};
template<> struct UnitTraits<NominalSolarRadiusTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NOMINAL_SOLAR_RADIUS; }
};
template<> struct UnitTraits<NominalSolarDiameterTag> {
    static constexpr UnitId unit_id() { return UNIT_ID_NOMINAL_SOLAR_DIAMETER; }
};

// Type aliases for convenient usage - SI metric
using PlanckLength = Quantity<PlanckLengthTag>;
using Yoctometer = Quantity<YoctometerTag>;
using Zeptometer = Quantity<ZeptometerTag>;
using Attometer = Quantity<AttometerTag>;
using Femtometer = Quantity<FemtometerTag>;
using Picometer = Quantity<PicometerTag>;
using Nanometer = Quantity<NanometerTag>;
using Micrometer = Quantity<MicrometerTag>;
using Millimeter = Quantity<MillimeterTag>;
using Centimeter = Quantity<CentimeterTag>;
using Decimeter = Quantity<DecimeterTag>;
using Meter = Quantity<MeterTag>;
using Decameter = Quantity<DecameterTag>;
using Hectometer = Quantity<HectometerTag>;
using Kilometer = Quantity<KilometerTag>;
using Megameter = Quantity<MegameterTag>;
using Gigameter = Quantity<GigameterTag>;
using Terameter = Quantity<TerameterTag>;
using Petameter = Quantity<PetameterTag>;
using Exameter = Quantity<ExameterTag>;
using Zettameter = Quantity<ZettameterTag>;
using Yottameter = Quantity<YottameterTag>;

// Type aliases for astronomical units
using BohrRadius = Quantity<BohrRadiusTag>;
using ClassicalElectronRadius = Quantity<ClassicalElectronRadiusTag>;
using ElectronReducedComptonWavelength = Quantity<ElectronReducedComptonWavelengthTag>;
using AstronomicalUnit = Quantity<AstronomicalUnitTag>;
using LightYear = Quantity<LightYearTag>;
using Parsec = Quantity<ParsecTag>;
using Kiloparsec = Quantity<KiloparsecTag>;
using Megaparsec = Quantity<MegaparsecTag>;
using Gigaparsec = Quantity<GigaparsecTag>;

// Type aliases for imperial units
using Inch = Quantity<InchTag>;
using Foot = Quantity<FootTag>;
using Yard = Quantity<YardTag>;
using Mile = Quantity<MileTag>;

// Type aliases for nautical units
using Link = Quantity<LinkTag>;
using Fathom = Quantity<FathomTag>;
using Rod = Quantity<RodTag>;
using Chain = Quantity<ChainTag>;
using NauticalMile = Quantity<NauticalMileTag>;

// Type aliases for nominal units
using NominalLunarRadius = Quantity<NominalLunarRadiusTag>;
using NominalLunarDistance = Quantity<NominalLunarDistanceTag>;
using NominalEarthPolarRadius = Quantity<NominalEarthPolarRadiusTag>;
using NominalEarthRadius = Quantity<NominalEarthRadiusTag>;
using NominalEarthEquatorialRadius = Quantity<NominalEarthEquatorialRadiusTag>;
using EarthMeridionalCircumference = Quantity<EarthMeridionalCircumferenceTag>;
using EarthEquatorialCircumference = Quantity<EarthEquatorialCircumferenceTag>;
using NominalJupiterRadius = Quantity<NominalJupiterRadiusTag>;
using NominalSolarRadius = Quantity<NominalSolarRadiusTag>;
using NominalSolarDiameter = Quantity<NominalSolarDiameterTag>;

} // namespace qtty
