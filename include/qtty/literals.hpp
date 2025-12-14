#pragma once

#include "units/length_ffi.hpp"
#include "units/time_ffi.hpp"
#include "units/angular_ffi.hpp"

namespace qtty {

// Inline namespace for user-defined literals
inline namespace literals {

// Length literals
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

// Time literals
constexpr Second operator""_s(long double value) {
    return Second(static_cast<double>(value));
}

constexpr Second operator""_s(unsigned long long value) {
    return Second(static_cast<double>(value));
}

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

// Angular literals
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

} // namespace literals

} // namespace qtty
