#pragma once

/**
 * @file qtty_ffi.hpp
 * @brief Main header for the qtty C++ wrapper library
 * 
 * This header provides a modern, type-safe C++ interface to the qtty-ffi library.
 * It includes:
 * - Template-based Quantity class with compile-time unit checking
 * - Operator overloading for natural arithmetic syntax
 * - User-defined literals for convenient quantity creation
 * - Support for length, time, angular, and compound (velocity) units
 * 
 * Usage example:
 * @code
 * using namespace qtty;
 * 
 * // Create quantities using constructors or literals
 * Meter distance(1000.0);
 * auto time = 20.0_s;
 * 
 * // Perform arithmetic operations
 * auto doubled = distance * 2.0;
 * 
 * // Convert units
 * Kilometer km = distance.to<Kilometer>();
 * 
 * // Create compound units (velocity)
 * auto velocity = distance / time;
 * @endcode
 */

// Core template definitions
#include "ffi_core.hpp"

// Unit-specific headers
#include "units/length_ffi.hpp"
#include "units/time_ffi.hpp"
#include "units/angular_ffi.hpp"
#include "units/velocity_ffi.hpp"

// User-defined literals
#include "literals.hpp"

namespace qtty {

/**
 * @brief Library version information
 */
inline constexpr struct {
    int major = 0;
    int minor = 1;
    int patch = 0;
} version;

/**
 * @brief Get the ABI version of the underlying qtty-ffi library
 * @return ABI version number
 */
inline uint32_t abi_version() {
    return qtty_ffi_version();
}

} // namespace qtty
