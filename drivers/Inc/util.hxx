#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include <cstdint>
#include <cmath>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

// Common bitwise operations.
#define MODIFY_FIELD(reg, field, value) ((reg) = ((reg)& ~ (field ## _Msk)) | (((uint32_t)(value) << field ## _Pos)& field ## _Msk))
#define MASK(x) (1UL << (x))

void float_to_parts(double input, uint32_t& integer_part, uint32_t& decimal_part);
float scale_value(float value, float minimum_value_expected, float maximum_value_expected, float target_minimum, float target_maximum);

#endif // UTIL_FILE_H
