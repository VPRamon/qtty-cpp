#include "fixtures.hpp"

TEST_F(PrecisionEdgeCaseTest, ZeroValues) {
    Meter m(0.0);
    EXPECT_EQ(m.value(), 0.0);

    auto m2 = m * 5.0;
    EXPECT_EQ(m2.value(), 0.0);

    Kilometer km = m.to<Kilometer>();
    EXPECT_EQ(km.value(), 0.0);
}

TEST_F(PrecisionEdgeCaseTest, LargeValues) {
    LightYear ly(1e9);
    EXPECT_EQ(ly.value(), 1e9);

    Parsec pc = ly.to<Parsec>();
    EXPECT_GT(pc.value(), 0.0);
}

TEST_F(PrecisionEdgeCaseTest, VerySmallValues) {
    Nanometer nm(0.1);
    Picometer pm = nm.to<Picometer>();
    EXPECT_NEAR(pm.value(), 100.0, 1e-12);

    Nanosecond ns(0.5);
    Picosecond ps = ns.to<Picosecond>();
    EXPECT_NEAR(ps.value(), 500.0, 1e-12);
}
