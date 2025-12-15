#pragma once

#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
extern "C" {
#include "qtty_ffi.h"
}
#include "ffi_core.hpp"

// Forward declarations for JSON-related FFI functions. These may not be present
// in older generated headers; we declare them here to ensure availability at
// compile time when linking against a serde-enabled qtty-ffi.
extern "C" {
int32_t qtty_quantity_to_json_value(qtty_quantity_t src, char** out_json);
int32_t qtty_quantity_from_json_value(UnitId unit, const char* json, qtty_quantity_t* out);
int32_t qtty_quantity_to_json(qtty_quantity_t src, char** out_json);
int32_t qtty_quantity_from_json(const char* json, qtty_quantity_t* out);
void qtty_string_free(char* s);
}

namespace qtty {
namespace serialization {

// Thin wrappers over Rust FFI JSON serialize/deserialize.
// Requires qtty-ffi to be built with the `serde` Cargo feature.

inline std::string from_owned_c(char* ptr) {
    if (!ptr) return {};
    std::string s(ptr);
    // Free via FFI allocator
    qtty_string_free(ptr);
    return s;
}

// Serialize only the numeric value as a JSON number string.
// Mirrors Rust's default serde for quantities.

template<typename UnitTag>
std::string to_json_value(const Quantity<UnitTag>& q) {
    qtty_quantity_t src{};
    int32_t status = qtty_quantity_make(q.value(), UnitTraits<UnitTag>::unit_id(), &src);
    check_status(status, "Creating source quantity for to_json_value");

    char* out = nullptr;
    status = qtty_quantity_to_json_value(src, &out);
    check_status(status, "Serializing value to JSON");
    return from_owned_c(out);
}

template<typename T>
Quantity<typename ExtractTag<T>::type> from_json_value(std::string_view json) {
    using UnitTag = typename ExtractTag<T>::type;
    qtty_quantity_t out_qty{};
    int32_t status = qtty_quantity_from_json_value(UnitTraits<UnitTag>::unit_id(),
                                                   json.data(), &out_qty);
    check_status(status, "Deserializing value from JSON");
    return Quantity<UnitTag>(out_qty.value);
}

// Serialize value and unit_id into an object {"value":<f64>, "unit_id":<u32>}.

template<typename UnitTag>
std::string to_json(const Quantity<UnitTag>& q) {
    qtty_quantity_t src{};
    int32_t status = qtty_quantity_make(q.value(), UnitTraits<UnitTag>::unit_id(), &src);
    check_status(status, "Creating source quantity for to_json");

    char* out = nullptr;
    status = qtty_quantity_to_json(src, &out);
    check_status(status, "Serializing quantity to JSON");
    return from_owned_c(out);
}

inline UnitId unit_id_from_u32(uint32_t raw) {
    // cbindgen exposes UnitId directly; cast is safe for values from Rust
    return static_cast<UnitId>(raw);
}

// Parse {"value":<f64>, "unit_id":<u32>} and construct a typed quantity.
// Rejects mismatched dimensions and unknown unit_ids at the Rust boundary.

template<typename T>
Quantity<typename ExtractTag<T>::type> from_json(std::string_view json) {
    using UnitTag = typename ExtractTag<T>::type;
    qtty_quantity_t out_qty{};
    int32_t status = qtty_quantity_from_json(json.data(), &out_qty);
    check_status(status, "Deserializing quantity from JSON");

    // Convert to requested UnitTag if needed; Rust returns the unit in JSON
    if (out_qty.unit != UnitTraits<UnitTag>::unit_id()) {
        qtty_quantity_t conv{};
        status = qtty_quantity_convert(out_qty, UnitTraits<UnitTag>::unit_id(), &conv);
        check_status(status, "Converting deserialized quantity to target unit");
        return Quantity<UnitTag>(conv.value);
    }
    return Quantity<UnitTag>(out_qty.value);
}

} // namespace serialization
} // namespace qtty
