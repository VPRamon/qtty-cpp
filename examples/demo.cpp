#include <iostream>
#include <iomanip>
#include "qtty/qtty_ffi.hpp"

using namespace qtty;

int main() {
    std::cout << "=== qtty-cpp Demo ===" << std::endl;
    std::cout << "FFI ABI Version: " << abi_version() << "\n" << std::endl;
    
    // Example 1: Basic construction and conversion
    std::cout << "1. Distance Conversion:" << std::endl;
    Meter distance(1500.0);
    std::cout << "   Distance: " << distance.value() << " m" << std::endl;
    
    Kilometer km = distance.to<Kilometer>();
    std::cout << "   Distance: " << km.value() << " km" << std::endl;
    
    // Example 2: Using literals
    std::cout << "\n2. Using Literals:" << std::endl;
    auto height = 10.5_m;
    auto width = 5.0_m;
    auto area_side = height + width;
    std::cout << "   Height: " << height.value() << " m" << std::endl;
    std::cout << "   Width: " << width.value() << " m" << std::endl;
    std::cout << "   Sum: " << area_side.value() << " m" << std::endl;
    
    // Example 3: Velocity calculation
    std::cout << "\n3. Velocity Calculation:" << std::endl;
    auto car_distance = 100.0_km;
    auto travel_time = 2.0_h;
    auto speed = car_distance / travel_time;
    std::cout << "   Distance: " << car_distance.value() << " km" << std::endl;
    std::cout << "   Time: " << travel_time.value() << " h" << std::endl;
    std::cout << "   Speed: " << speed.value() << " km/h" << std::endl;
    
    // Example 4: Angular conversions
    std::cout << "\n4. Angular Conversions:" << std::endl;
    auto angle_deg = 180.0_deg;
    Radian angle_rad = angle_deg.to<Radian>();
    std::cout << "   Angle: " << angle_deg.value() << " degrees" << std::endl;
    std::cout << std::setprecision(6);
    std::cout << "   Angle: " << angle_rad.value() << " radians" << std::endl;
    
    // Example 5: Time conversions
    std::cout << "\n5. Time Conversions:" << std::endl;
    auto duration_seconds = 3665.0_s;
    Hour duration_hours = duration_seconds.to<Hour>();
    Minute duration_minutes = duration_seconds.to<Minute>();
    std::cout << "   Duration: " << duration_seconds.value() << " seconds" << std::endl;
    std::cout << std::setprecision(4);
    std::cout << "   Duration: " << duration_hours.value() << " hours" << std::endl;
    std::cout << std::setprecision(2);
    std::cout << "   Duration: " << duration_minutes.value() << " minutes" << std::endl;
    
    // Example 6: Compound operations
    std::cout << "\n6. Compound Operations:" << std::endl;
    Meter total(100.0);
    std::cout << "   Initial: " << total.value() << " m" << std::endl;
    
    total += 50.0_m;
    std::cout << "   After += 50m: " << total.value() << " m" << std::endl;
    
    total *= 2.0;
    std::cout << "   After *= 2: " << total.value() << " m" << std::endl;
    
    total /= 3.0;
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "   After /= 3: " << total.value() << " m" << std::endl;
    
    // Example 7: Comparisons
    std::cout << "\n7. Comparisons:" << std::endl;
    auto length1 = 10.0_m;
    auto length2 = 5.0_m;
    std::cout << "   " << length1.value() << "m > " << length2.value() << "m? " 
              << (length1 > length2 ? "Yes" : "No") << std::endl;
    std::cout << "   " << length1.value() << "m == " << length2.value() << "m? " 
              << (length1 == length2 ? "Yes" : "No") << std::endl;
    
    // Example 8: Absolute value and negation
    std::cout << "\n8. Absolute Value and Negation:" << std::endl;
    Meter negative(-42.5);
    auto positive = negative.abs();
    auto double_negative = -negative;
    std::cout << "   Original: " << negative.value() << " m" << std::endl;
    std::cout << "   Absolute: " << positive.value() << " m" << std::endl;
    std::cout << "   Negated: " << double_negative.value() << " m" << std::endl;
    
    std::cout << "\n=== All examples completed successfully! ===" << std::endl;
    
    return 0;
}
