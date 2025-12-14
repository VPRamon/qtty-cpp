#pragma once

#include <gtest/gtest.h>
#include <cmath>
#include "qtty/qtty.hpp"

// Provide qtty symbols directly for each test translation unit.
using namespace qtty;

class QttyTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class LengthDimensionTest : public QttyTest {};
class TimeDimensionTest : public QttyTest {};
class AngularDimensionTest : public QttyTest {};
class MassDimensionTest : public QttyTest {};
class PowerDimensionTest : public QttyTest {};
class DerivedQuantityTest : public QttyTest {};
class QuantityOperationsTest : public QttyTest {};
class DimensionSafetyTest : public QttyTest {};
class PrecisionEdgeCaseTest : public QttyTest {};
