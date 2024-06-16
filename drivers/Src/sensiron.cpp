#include "sensiron.hxx"

// Convert raw temperature ticks to degrees Celsius
int convert_temp(uint16_t temp_ticks, uint8_t crc) {
    return -49 + (315 * temp_ticks) / 65535;
}

// Convert raw humidity ticks to percentage relative humidity
int convert_humidity(uint16_t rh_ticks, uint8_t crc) {
    int rh_pRH = -6 + (125 * rh_ticks) / 65535;
    return (rh_pRH > 100) ? 100 : (rh_pRH < 0) ? 0 : rh_pRH;
}

int read_sht40(I2C& i2c, long& temperature, long& humidity) {
    int i2c_result = 0;
    char command[1] = {SHT4X_CMD_MEASURE_HPM};
    char data[6];

    // Write command to initiate measurement
    i2c_result = i2c.write(SHT40AD1B_I2C_ADDR, command, 1);
    if (i2c_result > 0) {
        printf("I2C command write failure: Code=%i\n", i2c_result);
        return i2c_result;
    }

    // Wait for measurement completion
    ThisThread::sleep_for(90ms);

    // Read data
    i2c_result = i2c.read(SHT40AD1B_I2C_ADDR, data, 6);
    if (i2c_result > 0) {
        printf("I2C HPM read failure: Code=%i\n", i2c_result);
        return i2c_result;
    }

    // Extract temperature and humidity data
    uint16_t t_ticks = data[0] * 256 + data[1];
    uint8_t checksum_t = data[2];
    uint16_t rh_ticks = data[3] * 256 + data[4];
    uint8_t checksum_rh = data[5];

    temperature = convert_temp(t_ticks, checksum_t);
    humidity = convert_humidity(rh_ticks, checksum_rh);

    // printf("Read successful: temp=%" PRId32 "°C\thumidity=%" PRId32 "%%\n", temperature, humidity);
    return i2c_result;
}
