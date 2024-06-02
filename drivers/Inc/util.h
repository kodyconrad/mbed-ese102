#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif // UTIL_FILE_H