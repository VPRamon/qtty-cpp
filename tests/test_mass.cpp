#include "fixtures.hpp"

TEST_F(MassDimensionTest, MassUnitsBasic) {
    auto g_val = 1000.0_g;
    EXPECT_EQ(g_val.value(), 1000.0);

    auto kg_val = 2.5_kg;
    EXPECT_EQ(kg_val.value(), 2.5);
}

TEST_F(MassDimensionTest, MassConversions) {
    auto g_val = 1000.0_g;
    Kilogram kg = g_val.to<Kilogram>();
    EXPECT_NEAR(kg.value(), 1.0, 1e-12);

    auto kg_val = 2.5_kg;
    Gram g = kg_val.to<Gram>();
    EXPECT_NEAR(g.value(), 2500.0, 1e-9);

    auto mg_val = 5000.0_mg;
    Gram g2 = mg_val.to<Gram>();
    EXPECT_NEAR(g2.value(), 5.0, 1e-12);

    auto t_val = 1.0_t;
    Kilogram kg2 = t_val.to<Kilogram>();
    EXPECT_NEAR(kg2.value(), 1000.0, 1e-9);
}

TEST_F(MassDimensionTest, ImperialMassConversions) {
    auto lb_val = 1.0_lb;
    Kilogram kg = lb_val.to<Kilogram>();
    EXPECT_NEAR(kg.value(), 0.45359237, 1e-9);

    auto oz_val = 1.0_oz;
    Gram g = oz_val.to<Gram>();
    EXPECT_NEAR(g.value(), 28.349523125, 1e-9);

    auto lb_val2 = 1.0_lb;
    Ounce oz = lb_val2.to<Ounce>();
    EXPECT_NEAR(oz.value(), 16.0, 1e-9);
}

TEST_F(MassDimensionTest, MassArithmetic) {
    Kilogram kg1(5.0);
    Kilogram kg2(3.0);

    auto sum = kg1 + kg2;
    EXPECT_EQ(sum.value(), 8.0);

    auto diff = kg1 - kg2;
    EXPECT_EQ(diff.value(), 2.0);

    auto scaled = kg1 * 2.0;
    EXPECT_EQ(scaled.value(), 10.0);
}
