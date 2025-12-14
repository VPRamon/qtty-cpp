#include <gtest/gtest.h>
#include <cmath>
#include "qtty/qtty_ffi.hpp"

using namespace qtty;

// Test fixture for qtty tests
class QttyTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }
    
    void TearDown() override {
        // Cleanup code if needed
    }
};

TEST_F(QttyTest, MeterConstruction) {
    Meter m1(5.0);
    EXPECT_EQ(m1.value(), 5.0);
    
    auto m2 = 10.0_m;
    EXPECT_EQ(m2.value(), 10.0);
}

TEST_F(QttyTest, MeterArithmetic) {
    Meter a(10.0);
    Meter b(3.0);
    
    auto sum = a + b;
    EXPECT_EQ(sum.value(), 13.0);
    
    auto diff = a - b;
    EXPECT_EQ(diff.value(), 7.0);
    
    auto scaled = a * 2.0;
    EXPECT_EQ(scaled.value(), 20.0);
    
    auto divided = a / 2.0;
    EXPECT_EQ(divided.value(), 5.0);
}

TEST_F(QttyTest, MeterComparison) {
    Meter a(10.0);
    Meter b(5.0);
    Meter c(10.0);
    
    EXPECT_EQ(a, c);
    EXPECT_NE(a, b);
    EXPECT_GT(a, b);
    EXPECT_LT(b, a);
    EXPECT_GE(a, c);
    EXPECT_LE(a, c);
}

TEST_F(QttyTest, UnitConversion) {
    Meter m(1000.0);
    Kilometer km = m.to<Kilometer>();
    
    EXPECT_NEAR(km.value(), 1.0, 1e-12);
    
    Meter m2 = km.to<Meter>();
    EXPECT_NEAR(m2.value(), 1000.0, 1e-9);
}

TEST_F(QttyTest, CompoundAssignment) {
    Meter m(10.0);
    m += Meter(5.0);
    EXPECT_EQ(m.value(), 15.0);
    
    m -= Meter(3.0);
    EXPECT_EQ(m.value(), 12.0);
    
    m *= 2.0;
    EXPECT_EQ(m.value(), 24.0);
    
    m /= 4.0;
    EXPECT_EQ(m.value(), 6.0);
}

TEST_F(QttyTest, TimeUnits) {
    Second s1(60.0);
    Second s2(30.0);
    
    auto sum = s1 + s2;
    EXPECT_EQ(sum.value(), 90.0);
    
    auto diff = s1 - s2;
    EXPECT_EQ(diff.value(), 30.0);
    
    auto literal = 10.0_s;
    EXPECT_EQ(literal.value(), 10.0);
}

TEST_F(QttyTest, AbsAndNegation) {
    Meter m(-5.5);
    EXPECT_EQ(m.abs().value(), 5.5);
    
    Meter neg = -m;
    EXPECT_EQ(neg.value(), 5.5);
}

TEST_F(QttyTest, VelocityCreation) {
    // Create velocity by division
    Meter distance(100.0);
    Second time(20.0);
    auto velocity = distance / time;
    
    EXPECT_NEAR(velocity.value(), 5.0, 1e-12);
    
    // Direct construction
    Velocity<Meter, Second> v1(10.0);
    EXPECT_EQ(v1.value(), 10.0);
}

TEST_F(QttyTest, ScalarMultiplication) {
    Meter m(10.0);
    
    // Test both orderings
    auto result1 = m * 3.0;
    auto result2 = 3.0 * m;
    
    EXPECT_EQ(result1.value(), 30.0);
    EXPECT_EQ(result2.value(), 30.0);
}

TEST_F(QttyTest, AngularConversions) {
    auto angle_deg = 180.0_deg;
    Radian angle_rad = angle_deg.to<Radian>();
    
    EXPECT_NEAR(angle_rad.value(), 3.14159265, 1e-6);
    
    // Convert back
    Degree back_deg = angle_rad.to<Degree>();
    EXPECT_NEAR(back_deg.value(), 180.0, 1e-9);
}

TEST_F(QttyTest, TimeConversions) {
    auto duration_seconds = 3600.0_s;
    Hour duration_hours = duration_seconds.to<Hour>();
    
    EXPECT_NEAR(duration_hours.value(), 1.0, 1e-12);
    
    Minute duration_minutes = duration_seconds.to<Minute>();
    EXPECT_NEAR(duration_minutes.value(), 60.0, 1e-9);
}

TEST_F(QttyTest, ExceptionHandling) {
    // Test that incompatible dimension conversions throw
    Meter m(100.0);
    
    EXPECT_THROW({
        // This should throw IncompatibleDimensionsError
        // since we can't convert length to time
        qtty_quantity_t qty;
        qtty_quantity_make(100.0, UNIT_ID_METER, &qty);
        qtty_quantity_t result;
        int32_t status = qtty_quantity_convert(qty, UNIT_ID_SECOND, &result);
        check_status(status, "Invalid conversion");
    }, IncompatibleDimensionsError);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
