#pragma once

#include <cmath>
#include <stdexcept>
#include <string>
#include <type_traits>
extern "C" {
#include "qtty_ffi.h"
}

namespace qtty {

// Exception types for error handling
class QttyException : public std::runtime_error {
public:
    explicit QttyException(const std::string& msg) : std::runtime_error(msg) {}
};

class InvalidUnitError : public QttyException {
public:
    explicit InvalidUnitError(const std::string& msg) : QttyException(msg) {}
};

class IncompatibleDimensionsError : public QttyException {
public:
    explicit IncompatibleDimensionsError(const std::string& msg) : QttyException(msg) {}
};

class ConversionError : public QttyException {
public:
    explicit ConversionError(const std::string& msg) : QttyException(msg) {}
};

// Helper function to check status and throw appropriate exceptions
inline void check_status(int32_t status, const char* operation) {
    if (status == QTTY_OK) {
        return;
    }
    
    std::string msg = std::string(operation) + " failed: ";
    switch (status) {
        case QTTY_ERR_UNKNOWN_UNIT:
            throw InvalidUnitError(msg + "unknown unit");
        case QTTY_ERR_INCOMPATIBLE_DIM:
            throw IncompatibleDimensionsError(msg + "incompatible dimensions");
        case QTTY_ERR_NULL_OUT:
            throw QttyException(msg + "null output pointer");
        case QTTY_ERR_INVALID_VALUE:
            throw ConversionError(msg + "invalid value");
        default:
            throw QttyException(msg + "unknown error");
    }
}

// Forward declarations
template<typename UnitTag>
class Quantity;

// Template trait to get unit ID from unit tag
template<typename UnitTag>
struct UnitTraits;

// Helper to extract tag from either a tag or Quantity<Tag>
template<typename T>
struct ExtractTag {
    using type = T;
};

template<typename Tag>
struct ExtractTag<Quantity<Tag>> {
    using type = Tag;
};

// Base Quantity template class
template<typename UnitTag>
class Quantity {
private:
    double m_value;
    
public:
    using unit_tag = UnitTag;
    
    // Constructors
    constexpr Quantity() : m_value(0.0) {}
    constexpr explicit Quantity(double value) : m_value(value) {}
    
    // Get the unit ID for this quantity type
    static constexpr UnitId unit_id() {
        return UnitTraits<UnitTag>::unit_id();
    }
    
    // Get the raw value
    constexpr double value() const {
        return m_value;
    }
    
    // Convert to another unit type (accepts either Tag or Quantity<Tag>)
    template<typename TargetType>
    Quantity<typename ExtractTag<TargetType>::type> to() const {
        using TargetTag = typename ExtractTag<TargetType>::type;
        qtty_quantity_t src_qty;
        qtty_quantity_t dst_qty;
        
        int32_t status = qtty_quantity_make(m_value, unit_id(), &src_qty);
        check_status(status, "Creating source quantity");
        
        status = qtty_quantity_convert(src_qty, UnitTraits<TargetTag>::unit_id(), &dst_qty);
        check_status(status, "Converting units");
        
        return Quantity<TargetTag>(dst_qty.value);
    }
    
    // Arithmetic operators - same unit
    Quantity operator+(const Quantity& other) const {
        return Quantity(m_value + other.m_value);
    }
    
    Quantity operator-(const Quantity& other) const {
        return Quantity(m_value - other.m_value);
    }
    
    // Scalar multiplication and division
    Quantity operator*(double scalar) const {
        return Quantity(m_value * scalar);
    }
    
    Quantity operator/(double scalar) const {
        return Quantity(m_value / scalar);
    }
    
    // Friend function for scalar * quantity
    friend Quantity operator*(double scalar, const Quantity& q) {
        return q * scalar;
    }
    
    // Comparison operators
    bool operator==(const Quantity& other) const {
        return m_value == other.m_value;
    }
    
    bool operator!=(const Quantity& other) const {
        return m_value != other.m_value;
    }
    
    bool operator<(const Quantity& other) const {
        return m_value < other.m_value;
    }
    
    bool operator>(const Quantity& other) const {
        return m_value > other.m_value;
    }
    
    bool operator<=(const Quantity& other) const {
        return m_value <= other.m_value;
    }
    
    bool operator>=(const Quantity& other) const {
        return m_value >= other.m_value;
    }
    
    // Compound assignment operators
    Quantity& operator+=(const Quantity& other) {
        m_value += other.m_value;
        return *this;
    }
    
    Quantity& operator-=(const Quantity& other) {
        m_value -= other.m_value;
        return *this;
    }
    
    Quantity& operator*=(double scalar) {
        m_value *= scalar;
        return *this;
    }
    
    Quantity& operator/=(double scalar) {
        m_value /= scalar;
        return *this;
    }
    
    // Unary operators
    Quantity operator-() const {
        return Quantity(-m_value);
    }
    
    Quantity abs() const {
        return Quantity(std::abs(m_value));
    }
};

} // namespace qtty
