#include "util.hxx"

// Separate a floating-point number into integer and decimal parts
void float_to_parts(double input, uint32_t& integer_part, uint32_t& decimal_part) {
    double fractional;
    fractional = std::modf(input, (double*)&integer_part); // Cast to double* for modf
    decimal_part = static_cast<uint32_t>(fractional * 100); // Convert fractional part to uint32_t (scaled by 100)
}

// Scale a float value based on the range expected to the range output desired.
float scale_value(float value, float minimum_value_expected, float maximum_value_expected, float target_minimum, float target_maximum) {
    float original_range = maximum_value_expected - minimum_value_expected;
    float target_range = target_maximum - target_minimum;
    float scaling_factor = target_range / original_range;

    // Map the value
    float mappedValue = (value - minimum_value_expected) * scaling_factor + target_minimum;

    return mappedValue;
}
