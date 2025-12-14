#include "fixtures.hpp"

TEST_F(LengthDimensionTest, MeterConstruction) {
    Meter m1(5.0);
    EXPECT_EQ(m1.value(), 5.0);

    auto m2 = 10.0_m;
    EXPECT_EQ(m2.value(), 10.0);
}

TEST_F(LengthDimensionTest, MeterArithmetic) {
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

TEST_F(LengthDimensionTest, MeterComparison) {
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

TEST_F(LengthDimensionTest, LengthUnitConversions) {
    Meter m(1000.0);
    Kilometer km = m.to<Kilometer>();
    EXPECT_NEAR(km.value(), 1.0, 1e-12);

    Meter m2 = km.to<Meter>();
    EXPECT_NEAR(m2.value(), 1000.0, 1e-9);

    auto mm_val = 5000.0_mm;
    Meter m3 = mm_val.to<Meter>();
    EXPECT_NEAR(m3.value(), 5.0, 1e-12);

    auto inch_val = 12.0_in;
    Centimeter cm = inch_val.to<Centimeter>();
    EXPECT_NEAR(cm.value(), 30.48, 1e-9);

    auto mile_val = 1.0_mi;
    Kilometer km2 = mile_val.to<Kilometer>();
    EXPECT_NEAR(km2.value(), 1.609344, 1e-9);
}

TEST_F(LengthDimensionTest, AstronomicalLengthUnits) {
    auto au_val = 1.0_au;
    Meter m = au_val.to<Meter>();
    EXPECT_NEAR(m.value(), 149597870700.0, 1e-6);

    auto ly_val = 1.0_ly;
    Kilometer km = ly_val.to<Kilometer>();
    EXPECT_GT(km.value(), 9.4e12);

    auto pc_val = 1.0_pc;
    LightYear ly2 = pc_val.to<LightYear>();
    EXPECT_NEAR(ly2.value(), 3.26156, 1e-4);
}

TEST_F(LengthDimensionTest, SmallLengthUnits) {
    auto nm_val = 500.0_nm;
    Micrometer um = nm_val.to<Micrometer>();
    EXPECT_NEAR(um.value(), 0.5, 1e-12);

    Picometer pm(1000.0);
    Nanometer nm2 = pm.to<Nanometer>();
    EXPECT_NEAR(nm2.value(), 1.0, 1e-12);
}
