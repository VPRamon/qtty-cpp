#pragma once

#include "units/length_ffi.hpp"
#include "units/time_ffi.hpp"
#include "units/angular_ffi.hpp"
#include "units/mass_ffi.hpp"
#include "units/power_ffi.hpp"

namespace qtty {

// Inline namespace for user-defined literals
inline namespace literals {

// ====================
// Length literals
// ====================

// SI metric length literals
constexpr Nanometer operator""_nm(long double value) {
    return Nanometer(static_cast<double>(value));
}
constexpr Nanometer operator""_nm(unsigned long long value) {
    return Nanometer(static_cast<double>(value));
}

constexpr Micrometer operator""_um(long double value) {
    return Micrometer(static_cast<double>(value));
}
constexpr Micrometer operator""_um(unsigned long long value) {
    return Micrometer(static_cast<double>(value));
}

constexpr Millimeter operator""_mm(long double value) {
    return Millimeter(static_cast<double>(value));
}
constexpr Millimeter operator""_mm(unsigned long long value) {
    return Millimeter(static_cast<double>(value));
}

constexpr Centimeter operator""_cm(long double value) {
    return Centimeter(static_cast<double>(value));
}
constexpr Centimeter operator""_cm(unsigned long long value) {
    return Centimeter(static_cast<double>(value));
}

constexpr Meter operator""_m(long double value) {
    return Meter(static_cast<double>(value));
}
constexpr Meter operator""_m(unsigned long long value) {
    return Meter(static_cast<double>(value));
}

constexpr Kilometer operator""_km(long double value) {
    return Kilometer(static_cast<double>(value));
}
constexpr Kilometer operator""_km(unsigned long long value) {
    return Kilometer(static_cast<double>(value));
}

// Astronomical length literals
constexpr AstronomicalUnit operator""_au(long double value) {
    return AstronomicalUnit(static_cast<double>(value));
}
constexpr AstronomicalUnit operator""_au(unsigned long long value) {
    return AstronomicalUnit(static_cast<double>(value));
}

constexpr LightYear operator""_ly(long double value) {
    return LightYear(static_cast<double>(value));
}
constexpr LightYear operator""_ly(unsigned long long value) {
    return LightYear(static_cast<double>(value));
}

constexpr Parsec operator""_pc(long double value) {
    return Parsec(static_cast<double>(value));
}
constexpr Parsec operator""_pc(unsigned long long value) {
    return Parsec(static_cast<double>(value));
}

// Imperial length literals
constexpr Inch operator""_in(long double value) {
    return Inch(static_cast<double>(value));
}
constexpr Inch operator""_in(unsigned long long value) {
    return Inch(static_cast<double>(value));
}

constexpr Foot operator""_ft(long double value) {
    return Foot(static_cast<double>(value));
}
constexpr Foot operator""_ft(unsigned long long value) {
    return Foot(static_cast<double>(value));
}

constexpr Mile operator""_mi(long double value) {
    return Mile(static_cast<double>(value));
}
constexpr Mile operator""_mi(unsigned long long value) {
    return Mile(static_cast<double>(value));
}

// ====================
// Time literals
// ====================

// SI metric time literals
constexpr Nanosecond operator""_ns(long double value) {
    return Nanosecond(static_cast<double>(value));
}
constexpr Nanosecond operator""_ns(unsigned long long value) {
    return Nanosecond(static_cast<double>(value));
}

constexpr Microsecond operator""_us(long double value) {
    return Microsecond(static_cast<double>(value));
}
constexpr Microsecond operator""_us(unsigned long long value) {
    return Microsecond(static_cast<double>(value));
}

constexpr Millisecond operator""_ms(long double value) {
    return Millisecond(static_cast<double>(value));
}
constexpr Millisecond operator""_ms(unsigned long long value) {
    return Millisecond(static_cast<double>(value));
}

constexpr Second operator""_s(long double value) {
    return Second(static_cast<double>(value));
}
constexpr Second operator""_s(unsigned long long value) {
    return Second(static_cast<double>(value));
}

// Common time literals
constexpr Minute operator""_min(long double value) {
    return Minute(static_cast<double>(value));
}
constexpr Minute operator""_min(unsigned long long value) {
    return Minute(static_cast<double>(value));
}

constexpr Hour operator""_h(long double value) {
    return Hour(static_cast<double>(value));
}
constexpr Hour operator""_h(unsigned long long value) {
    return Hour(static_cast<double>(value));
}

constexpr Day operator""_d(long double value) {
    return Day(static_cast<double>(value));
}
constexpr Day operator""_d(unsigned long long value) {
    return Day(static_cast<double>(value));
}

constexpr Week operator""_wk(long double value) {
    return Week(static_cast<double>(value));
}
constexpr Week operator""_wk(unsigned long long value) {
    return Week(static_cast<double>(value));
}

constexpr Year operator""_yr(long double value) {
    return Year(static_cast<double>(value));
}
constexpr Year operator""_yr(unsigned long long value) {
    return Year(static_cast<double>(value));
}

// ====================
// Angular literals
// ====================

constexpr Radian operator""_rad(long double value) {
    return Radian(static_cast<double>(value));
}
constexpr Radian operator""_rad(unsigned long long value) {
    return Radian(static_cast<double>(value));
}

constexpr Degree operator""_deg(long double value) {
    return Degree(static_cast<double>(value));
}
constexpr Degree operator""_deg(unsigned long long value) {
    return Degree(static_cast<double>(value));
}

constexpr Arcminute operator""_arcmin(long double value) {
    return Arcminute(static_cast<double>(value));
}
constexpr Arcminute operator""_arcmin(unsigned long long value) {
    return Arcminute(static_cast<double>(value));
}

constexpr Arcsecond operator""_arcsec(long double value) {
    return Arcsecond(static_cast<double>(value));
}
constexpr Arcsecond operator""_arcsec(unsigned long long value) {
    return Arcsecond(static_cast<double>(value));
}

// ====================
// Mass literals
// ====================

constexpr Microgram operator""_ug(long double value) {
    return Microgram(static_cast<double>(value));
}
constexpr Microgram operator""_ug(unsigned long long value) {
    return Microgram(static_cast<double>(value));
}

constexpr Milligram operator""_mg(long double value) {
    return Milligram(static_cast<double>(value));
}
constexpr Milligram operator""_mg(unsigned long long value) {
    return Milligram(static_cast<double>(value));
}

constexpr Gram operator""_g(long double value) {
    return Gram(static_cast<double>(value));
}
constexpr Gram operator""_g(unsigned long long value) {
    return Gram(static_cast<double>(value));
}

constexpr Kilogram operator""_kg(long double value) {
    return Kilogram(static_cast<double>(value));
}
constexpr Kilogram operator""_kg(unsigned long long value) {
    return Kilogram(static_cast<double>(value));
}

constexpr Tonne operator""_t(long double value) {
    return Tonne(static_cast<double>(value));
}
constexpr Tonne operator""_t(unsigned long long value) {
    return Tonne(static_cast<double>(value));
}

// Imperial mass literals
constexpr Pound operator""_lb(long double value) {
    return Pound(static_cast<double>(value));
}
constexpr Pound operator""_lb(unsigned long long value) {
    return Pound(static_cast<double>(value));
}

constexpr Ounce operator""_oz(long double value) {
    return Ounce(static_cast<double>(value));
}
constexpr Ounce operator""_oz(unsigned long long value) {
    return Ounce(static_cast<double>(value));
}

// ====================
// Power literals
// ====================

constexpr Milliwatt operator""_mW(long double value) {
    return Milliwatt(static_cast<double>(value));
}
constexpr Milliwatt operator""_mW(unsigned long long value) {
    return Milliwatt(static_cast<double>(value));
}

constexpr Watt operator""_W(long double value) {
    return Watt(static_cast<double>(value));
}
constexpr Watt operator""_W(unsigned long long value) {
    return Watt(static_cast<double>(value));
}

constexpr Kilowatt operator""_kW(long double value) {
    return Kilowatt(static_cast<double>(value));
}
constexpr Kilowatt operator""_kW(unsigned long long value) {
    return Kilowatt(static_cast<double>(value));
}

constexpr Megawatt operator""_MW(long double value) {
    return Megawatt(static_cast<double>(value));
}
constexpr Megawatt operator""_MW(unsigned long long value) {
    return Megawatt(static_cast<double>(value));
}

constexpr Gigawatt operator""_GW(long double value) {
    return Gigawatt(static_cast<double>(value));
}
constexpr Gigawatt operator""_GW(unsigned long long value) {
    return Gigawatt(static_cast<double>(value));
}

} // namespace literals

} // namespace qtty
