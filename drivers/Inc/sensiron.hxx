#ifndef SENSIRON_H_FILE
#define SENSIRON_H_FILE
#include "mbed.h"
#include <cstdint>
/* all measurement commands return T (CRC) RH (CRC) */
const uint8_t SHT4X_CMD_MEASURE_HPM = 0xFD;
const uint8_t SHT4X_CMD_MEASURE_LPM = 0xE0;
const uint8_t SHT4X_CMD_READ_SERIAL = 0x89;
const uint16_t SHT4X_CMD_DURATION_USEC = 1000;
const uint8_t SHT4X_READ_DATA_SIZE = 6;
const uint8_t SHT40AD1B_I2C_ADDR = 0x89;

int convert_temp(uint16_t temp_ticks, uint8_t crc);
int convert_humidity(uint16_t rh_ticks, uint8_t crc);
int read_sht40(I2C& i2c, long& temperature, long& humidity);

#endif
