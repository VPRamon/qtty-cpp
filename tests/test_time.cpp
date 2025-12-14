#include "fixtures.hpp"

TEST_F(TimeDimensionTest, TimeUnits) {
    Second s1(60.0);
    Second s2(30.0);

    auto sum = s1 + s2;
    EXPECT_EQ(sum.value(), 90.0);

    auto diff = s1 - s2;
    EXPECT_EQ(diff.value(), 30.0);

    auto literal = 10.0_s;
    EXPECT_EQ(literal.value(), 10.0);
}

TEST_F(TimeDimensionTest, TimeConversions) {
    auto duration_seconds = 3600.0_s;
    Hour duration_hours = duration_seconds.to<Hour>();
    EXPECT_NEAR(duration_hours.value(), 1.0, 1e-12);

    Minute duration_minutes = duration_seconds.to<Minute>();
    EXPECT_NEAR(duration_minutes.value(), 60.0, 1e-9);

    auto day_val = 1.0_d;
    Hour hours = day_val.to<Hour>();
    EXPECT_NEAR(hours.value(), 24.0, 1e-12);

    auto week_val = 2.0_wk;
    Day days = week_val.to<Day>();
    EXPECT_NEAR(days.value(), 14.0, 1e-12);

    auto year_val = 1.0_yr;
    Day days2 = year_val.to<Day>();
    EXPECT_NEAR(days2.value(), 365.25, 1e-9);
}

TEST_F(TimeDimensionTest, SmallTimeUnits) {
    auto ms_val = 1000.0_ms;
    Second s = ms_val.to<Second>();
    EXPECT_NEAR(s.value(), 1.0, 1e-12);

    auto us_val = 5000.0_us;
    Millisecond ms2 = us_val.to<Millisecond>();
    EXPECT_NEAR(ms2.value(), 5.0, 1e-12);

    auto ns_val = 1000.0_ns;
    Microsecond us2 = ns_val.to<Microsecond>();
    EXPECT_NEAR(us2.value(), 1.0, 1e-12);
}
