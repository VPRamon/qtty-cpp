#include "fixtures.hpp"
#include "qtty/serialization.hpp"
#include <gtest/gtest.h>

using namespace qtty;

class SerializationTest : public QttyTest {};

TEST_F(SerializationTest, ValueOnlyRoundTrip) {
    Meter m(123.456789);
    auto s = serialization::to_json_value(m);
    auto m2 = serialization::from_json_value<Meter>(s);
    EXPECT_NEAR(m2.value(), m.value(), 1e-12);
}

TEST_F(SerializationTest, JsonWithUnitIdRoundTrip) {
    Kilometer km(1.2345);
    auto s = serialization::to_json(km);
    auto km2 = serialization::from_json<Kilometer>(s);
    EXPECT_NEAR(km2.value(), km.value(), 1e-12);
}

TEST_F(SerializationTest, JsonWithUnitIdAutoConvert) {
    // Serialize as km, deserialize into meters and ensure correct conversion
    Kilometer km(2.0);
    auto s = serialization::to_json(km);
    auto m = serialization::from_json<Meter>(s);
    EXPECT_NEAR(m.value(), 2000.0, 1e-12);
}

TEST_F(SerializationTest, ValueOnlyRejectsInvalidJson) {
    EXPECT_THROW((serialization::from_json_value<Meter>("not a number")), ConversionError);
}
