#include "fixtures.hpp"

TEST_F(PowerDimensionTest, PowerUnitsBasic) {
    auto w_val = 100.0_W;
    EXPECT_EQ(w_val.value(), 100.0);

    auto kw_val = 2.5_kW;
    EXPECT_EQ(kw_val.value(), 2.5);
}

TEST_F(PowerDimensionTest, PowerConversions) {
    auto w_val = 1000.0_W;
    Kilowatt kw = w_val.to<Kilowatt>();
    EXPECT_NEAR(kw.value(), 1.0, 1e-12);

    auto kw_val = 2.5_kW;
    Watt w = kw_val.to<Watt>();
    EXPECT_NEAR(w.value(), 2500.0, 1e-9);

    auto mw_val = 5000.0_mW;
    Watt w2 = mw_val.to<Watt>();
    EXPECT_NEAR(w2.value(), 5.0, 1e-12);

    auto MW_val = 1.0_MW;
    Kilowatt kw2 = MW_val.to<Kilowatt>();
    EXPECT_NEAR(kw2.value(), 1000.0, 1e-9);

    auto GW_val = 1.0_GW;
    Megawatt MW = GW_val.to<Megawatt>();
    EXPECT_NEAR(MW.value(), 1000.0, 1e-9);
}

TEST_F(PowerDimensionTest, PowerArithmetic) {
    Kilowatt kw1(5.0);
    Kilowatt kw2(3.0);

    auto sum = kw1 + kw2;
    EXPECT_EQ(sum.value(), 8.0);

    auto diff = kw1 - kw2;
    EXPECT_EQ(diff.value(), 2.0);

    auto scaled = kw1 * 2.0;
    EXPECT_EQ(scaled.value(), 10.0);
}
