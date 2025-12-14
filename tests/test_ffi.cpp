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

// ============================================================================
// LENGTH UNIT TESTS
// ============================================================================

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

TEST_F(QttyTest, LengthUnitConversions) {
    // Meter to Kilometer
    Meter m(1000.0);
    Kilometer km = m.to<Kilometer>();
    EXPECT_NEAR(km.value(), 1.0, 1e-12);
    
    // Kilometer back to Meter
    Meter m2 = km.to<Meter>();
    EXPECT_NEAR(m2.value(), 1000.0, 1e-9);
    
    // Millimeter to Meter
    auto mm_val = 5000.0_mm;
    Meter m3 = mm_val.to<Meter>();
    EXPECT_NEAR(m3.value(), 5.0, 1e-12);
    
    // Imperial: Inch to Centimeter
    auto inch_val = 12.0_in;
    Centimeter cm = inch_val.to<Centimeter>();
    EXPECT_NEAR(cm.value(), 30.48, 1e-9);
    
    // Mile to Kilometer
    auto mile_val = 1.0_mi;
    Kilometer km2 = mile_val.to<Kilometer>();
    EXPECT_NEAR(km2.value(), 1.609344, 1e-9);
}

TEST_F(QttyTest, AstronomicalLengthUnits) {
    // Astronomical Unit
    auto au_val = 1.0_au;
    Meter m = au_val.to<Meter>();
    EXPECT_NEAR(m.value(), 149597870700.0, 1e-6);
    
    // Light Year
    auto ly_val = 1.0_ly;
    Kilometer km = ly_val.to<Kilometer>();
    EXPECT_GT(km.value(), 9.4e12);
    
    // Parsec
    auto pc_val = 1.0_pc;
    LightYear ly2 = pc_val.to<LightYear>();
    EXPECT_NEAR(ly2.value(), 3.26156, 1e-4);
}

TEST_F(QttyTest, SmallLengthUnits) {
    // Nanometer
    auto nm_val = 500.0_nm;
    Micrometer um = nm_val.to<Micrometer>();
    EXPECT_NEAR(um.value(), 0.5, 1e-12);
    
    // Picometer to Nanometer
    Picometer pm(1000.0);
    Nanometer nm2 = pm.to<Nanometer>();
    EXPECT_NEAR(nm2.value(), 1.0, 1e-12);
}

// ============================================================================
// TIME UNIT TESTS
// ============================================================================

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

TEST_F(QttyTest, TimeConversions) {
    // Second to Hour
    auto duration_seconds = 3600.0_s;
    Hour duration_hours = duration_seconds.to<Hour>();
    EXPECT_NEAR(duration_hours.value(), 1.0, 1e-12);
    
    // Second to Minute
    Minute duration_minutes = duration_seconds.to<Minute>();
    EXPECT_NEAR(duration_minutes.value(), 60.0, 1e-9);
    
    // Day to Hour
    auto day_val = 1.0_d;
    Hour hours = day_val.to<Hour>();
    EXPECT_NEAR(hours.value(), 24.0, 1e-12);
    
    // Week to Day
    auto week_val = 2.0_wk;
    Day days = week_val.to<Day>();
    EXPECT_NEAR(days.value(), 14.0, 1e-12);
    
    // Year to Day
    auto year_val = 1.0_yr;
    Day days2 = year_val.to<Day>();
    EXPECT_NEAR(days2.value(), 365.25, 1e-9);
}

TEST_F(QttyTest, SmallTimeUnits) {
    // Millisecond to Second
    auto ms_val = 1000.0_ms;
    Second s = ms_val.to<Second>();
    EXPECT_NEAR(s.value(), 1.0, 1e-12);
    
    // Microsecond to Millisecond
    auto us_val = 5000.0_us;
    Millisecond ms2 = us_val.to<Millisecond>();
    EXPECT_NEAR(ms2.value(), 5.0, 1e-12);
    
    // Nanosecond to Microsecond
    auto ns_val = 1000.0_ns;
    Microsecond us2 = ns_val.to<Microsecond>();
    EXPECT_NEAR(us2.value(), 1.0, 1e-12);
}

// ============================================================================
// ANGULAR UNIT TESTS
// ============================================================================

TEST_F(QttyTest, AngularConversions) {
    auto angle_deg = 180.0_deg;
    Radian angle_rad = angle_deg.to<Radian>();
    
    EXPECT_NEAR(angle_rad.value(), 3.14159265, 1e-6);
    
    // Convert back
    Degree back_deg = angle_rad.to<Degree>();
    EXPECT_NEAR(back_deg.value(), 180.0, 1e-9);
}

TEST_F(QttyTest, AngularSubunits) {
    // 1 degree = 60 arcminutes
    Degree deg(1.0);
    Arcminute arcmin = deg.to<Arcminute>();
    EXPECT_NEAR(arcmin.value(), 60.0, 1e-9);
    
    // 1 arcminute = 60 arcseconds
    Arcminute arcmin2(1.0);
    Arcsecond arcsec = arcmin2.to<Arcsecond>();
    EXPECT_NEAR(arcsec.value(), 60.0, 1e-9);
    
    // 1 degree = 3600 arcseconds
    Degree deg2(1.0);
    Arcsecond arcsec2 = deg2.to<Arcsecond>();
    EXPECT_NEAR(arcsec2.value(), 3600.0, 1e-6);
}

TEST_F(QttyTest, RadianAndDegree) {
    // 360 degrees = 2π radians
    Degree full_circle(360.0);
    Radian rad = full_circle.to<Radian>();
    EXPECT_NEAR(rad.value(), 2.0 * M_PI, 1e-9);
    
    // 90 degrees = π/2 radians
    Degree right_angle(90.0);
    Radian rad2 = right_angle.to<Radian>();
    EXPECT_NEAR(rad2.value(), M_PI / 2.0, 1e-9);
}

// ============================================================================
// MASS UNIT TESTS
// ============================================================================

TEST_F(QttyTest, MassUnitsBasic) {
    // Gram construction
    auto g_val = 1000.0_g;
    EXPECT_EQ(g_val.value(), 1000.0);
    
    // Kilogram construction
    auto kg_val = 2.5_kg;
    EXPECT_EQ(kg_val.value(), 2.5);
}

TEST_F(QttyTest, MassConversions) {
    // Gram to Kilogram
    auto g_val = 1000.0_g;
    Kilogram kg = g_val.to<Kilogram>();
    EXPECT_NEAR(kg.value(), 1.0, 1e-12);
    
    // Kilogram to Gram
    auto kg_val = 2.5_kg;
    Gram g = kg_val.to<Gram>();
    EXPECT_NEAR(g.value(), 2500.0, 1e-9);
    
    // Milligram to Gram
    auto mg_val = 5000.0_mg;
    Gram g2 = mg_val.to<Gram>();
    EXPECT_NEAR(g2.value(), 5.0, 1e-12);
    
    // Tonne to Kilogram
    auto t_val = 1.0_t;
    Kilogram kg2 = t_val.to<Kilogram>();
    EXPECT_NEAR(kg2.value(), 1000.0, 1e-9);
}

TEST_F(QttyTest, ImperialMassConversions) {
    // Pound to Kilogram
    auto lb_val = 1.0_lb;
    Kilogram kg = lb_val.to<Kilogram>();
    EXPECT_NEAR(kg.value(), 0.45359237, 1e-9);
    
    // Ounce to Gram
    auto oz_val = 1.0_oz;
    Gram g = oz_val.to<Gram>();
    EXPECT_NEAR(g.value(), 28.349523125, 1e-9);
    
    // Pound to Ounce
    auto lb_val2 = 1.0_lb;
    Ounce oz = lb_val2.to<Ounce>();
    EXPECT_NEAR(oz.value(), 16.0, 1e-9);
}

TEST_F(QttyTest, MassArithmetic) {
    Kilogram kg1(5.0);
    Kilogram kg2(3.0);
    
    auto sum = kg1 + kg2;
    EXPECT_EQ(sum.value(), 8.0);
    
    auto diff = kg1 - kg2;
    EXPECT_EQ(diff.value(), 2.0);
    
    auto scaled = kg1 * 2.0;
    EXPECT_EQ(scaled.value(), 10.0);
}

// ============================================================================
// POWER UNIT TESTS
// ============================================================================

TEST_F(QttyTest, PowerUnitsBasic) {
    // Watt construction
    auto w_val = 100.0_W;
    EXPECT_EQ(w_val.value(), 100.0);
    
    // Kilowatt construction
    auto kw_val = 2.5_kW;
    EXPECT_EQ(kw_val.value(), 2.5);
}

TEST_F(QttyTest, PowerConversions) {
    // Watt to Kilowatt
    auto w_val = 1000.0_W;
    Kilowatt kw = w_val.to<Kilowatt>();
    EXPECT_NEAR(kw.value(), 1.0, 1e-12);
    
    // Kilowatt to Watt
    auto kw_val = 2.5_kW;
    Watt w = kw_val.to<Watt>();
    EXPECT_NEAR(w.value(), 2500.0, 1e-9);
    
    // Milliwatt to Watt
    auto mw_val = 5000.0_mW;
    Watt w2 = mw_val.to<Watt>();
    EXPECT_NEAR(w2.value(), 5.0, 1e-12);
    
    // Megawatt to Kilowatt
    auto MW_val = 1.0_MW;
    Kilowatt kw2 = MW_val.to<Kilowatt>();
    EXPECT_NEAR(kw2.value(), 1000.0, 1e-9);
    
    // Gigawatt to Megawatt
    auto GW_val = 1.0_GW;
    Megawatt MW = GW_val.to<Megawatt>();
    EXPECT_NEAR(MW.value(), 1000.0, 1e-9);
}

TEST_F(QttyTest, PowerArithmetic) {
    Kilowatt kw1(5.0);
    Kilowatt kw2(3.0);
    
    auto sum = kw1 + kw2;
    EXPECT_EQ(sum.value(), 8.0);
    
    auto diff = kw1 - kw2;
    EXPECT_EQ(diff.value(), 2.0);
    
    auto scaled = kw1 * 2.0;
    EXPECT_EQ(scaled.value(), 10.0);
}

// ============================================================================
// VELOCITY AND COMPOUND UNIT TESTS
// ============================================================================

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

// ============================================================================
// GENERAL OPERATION TESTS
// ============================================================================

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

TEST_F(QttyTest, AbsAndNegation) {
    Meter m(-5.5);
    EXPECT_EQ(m.abs().value(), 5.5);
    
    Meter neg = -m;
    EXPECT_EQ(neg.value(), 5.5);
}

TEST_F(QttyTest, ScalarMultiplication) {
    Meter m(10.0);
    
    // Test both orderings
    auto result1 = m * 3.0;
    auto result2 = 3.0 * m;
    
    EXPECT_EQ(result1.value(), 30.0);
    EXPECT_EQ(result2.value(), 30.0);
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

// ============================================================================
// EDGE CASE AND PRECISION TESTS
// ============================================================================

TEST_F(QttyTest, ZeroValues) {
    Meter m(0.0);
    EXPECT_EQ(m.value(), 0.0);
    
    auto m2 = m * 5.0;
    EXPECT_EQ(m2.value(), 0.0);
    
    Kilometer km = m.to<Kilometer>();
    EXPECT_EQ(km.value(), 0.0);
}

TEST_F(QttyTest, LargeValues) {
    // Test with astronomical distances
    LightYear ly(1e9);
    EXPECT_EQ(ly.value(), 1e9);
    
    // Convert to parsec
    Parsec pc = ly.to<Parsec>();
    EXPECT_GT(pc.value(), 0.0);
}

TEST_F(QttyTest, VerySmallValues) {
    // Test with atomic-scale lengths
    Nanometer nm(0.1);
    Picometer pm = nm.to<Picometer>();
    EXPECT_NEAR(pm.value(), 100.0, 1e-12);
    
    // Test with very small time scales
    Nanosecond ns(0.5);
    Picosecond ps = ns.to<Picosecond>();
    EXPECT_NEAR(ps.value(), 500.0, 1e-12);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
