#include "fixtures.hpp"

TEST_F(QuantityOperationsTest, CompoundAssignment) {
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

TEST_F(QuantityOperationsTest, AbsAndNegation) {
    Meter m(-5.5);
    EXPECT_EQ(m.abs().value(), 5.5);

    Meter neg = -m;
    EXPECT_EQ(neg.value(), 5.5);
}

TEST_F(QuantityOperationsTest, ScalarMultiplication) {
    Meter m(10.0);

    auto result1 = m * 3.0;
    auto result2 = 3.0 * m;

    EXPECT_EQ(result1.value(), 30.0);
    EXPECT_EQ(result2.value(), 30.0);
}
