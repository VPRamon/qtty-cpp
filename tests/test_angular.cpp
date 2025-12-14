#include "fixtures.hpp"

TEST_F(AngularDimensionTest, AngularConversions) {
    auto angle_deg = 180.0_deg;
    Radian angle_rad = angle_deg.to<Radian>();

    EXPECT_NEAR(angle_rad.value(), 3.14159265, 1e-6);

    Degree back_deg = angle_rad.to<Degree>();
    EXPECT_NEAR(back_deg.value(), 180.0, 1e-9);
}

TEST_F(AngularDimensionTest, AngularSubunits) {
    Degree deg(1.0);
    Arcminute arcmin = deg.to<Arcminute>();
    EXPECT_NEAR(arcmin.value(), 60.0, 1e-9);

    Arcminute arcmin2(1.0);
    Arcsecond arcsec = arcmin2.to<Arcsecond>();
    EXPECT_NEAR(arcsec.value(), 60.0, 1e-9);

    Degree deg2(1.0);
    Arcsecond arcsec2 = deg2.to<Arcsecond>();
    EXPECT_NEAR(arcsec2.value(), 3600.0, 1e-6);
}

TEST_F(AngularDimensionTest, RadianAndDegree) {
    Degree full_circle(360.0);
    Radian rad = full_circle.to<Radian>();
    EXPECT_NEAR(rad.value(), 2.0 * M_PI, 1e-9);

    Degree right_angle(90.0);
    Radian rad2 = right_angle.to<Radian>();
    EXPECT_NEAR(rad2.value(), M_PI / 2.0, 1e-9);
}
