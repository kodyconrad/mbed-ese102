#include "mbed.h"
#include "Inc\lcd.h"
#include "Sensiron\Inc\sht4x.h"

std::chrono::milliseconds duration(150);

// List Arduino compatible pins for connection for simultaneous use with IKS4A1
PinName LCD_SPI_SCK = D13;
PinName LCD_SPI_MOSI = D11;
PinName LCD_SPI_MISO = D12;
PinName LCD_SPI_CS = D10;
PinName LCD_LED_PWM = A0;

// LED Ticker
Ticker analog_update, led2_flasher, led3_flasher;
AnalogIn light_sensor(A1);

// I2C bus
PinName I2C1_SDA = D14;
PinName I2C1_SCL = D15;
I2C stm_i2c_bus(I2C1_SDA, I2C1_SCL);
/* all measurement commands return T (CRC) RH (CRC) */
const uint8_t SHT4X_CMD_MEASURE_HPM = 0xFD;
const uint8_t SHT4X_CMD_MEASURE_LPM = 0xE0;
const uint8_t SHT4X_CMD_READ_SERIAL = 0x89;
const uint16_t SHT4X_CMD_DURATION_USEC = 1000;
const uint8_t SHT4X_READ_DATA_SIZE = 6;
const uint8_t SHT40AD1B_I2C_ADDR = 0x89;

UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX);

// LCD Setup
DigitalOut lcd_cs(LCD_SPI_CS);
SPI serial_sr_lcd(LCD_SPI_MOSI, LCD_SPI_MISO, LCD_SPI_SCK);
LCD::LCDController display(serial_sr_lcd, lcd_cs);
PwmOut lcd_backlight(LCD_LED_PWM);
int32_t temp_raw = 0, hum_raw = 0;
volatile float light_percent_value = 0.25;


void float_to_parts(double input, uint32_t& integer_part, uint32_t& decimal_part);
float scale_value(float value, float minimum_value_expected, float maximum_value_expected, float target_minimum, float target_maximum);
int sht40_temp_conversion(uint16_t temp_ticks, uint8_t crc);
int sht40_hum_conversion(uint16_t rh_ticks, uint8_t crc);
int sh40_read(I2C& i2c, int32_t& temperature, int32_t& humidity);

int main() {
    // LCD Character string
    char lcd_line[20];
    printf("\n## ARM ESE102 - Module 1: Bonus Cascaded LCD Control (MBED Version: %d.%d.%d)##\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    //Backlight configure
    lcd_backlight.period(1/120.0);
    lcd_backlight.write(light_percent_value);
    printf("[Configuration] Backlight configured.");

    // LCD Serial channel configure.
    serial_sr_lcd.format(16,0); // Set up the SPI for 16 bit data (due to cascaded shift registers), mode 0.
    serial_sr_lcd.frequency(1000000); // Clock frequency is 1MHz
    lcd_cs=1;
    printf("[Configuration] Serial channel configured.\n");

    // Initialize display.
    display.initialize();
    ThisThread::sleep_for(100ms);
    display.clear();
    display.print("Temperature & ");
    display.command(0xC0);
    display.print("     Humidity");
    printf("[Configuration] Display initialized and cleared.\n");

    while (1) {
        display.command(0x2);
        sh40_read(stm_i2c_bus, temp_raw, hum_raw);
        sprintf(lcd_line, "Temperature: %" PRId32 "F", temp_raw);
        display.print(lcd_line);
        display.command(0xC0);
        sprintf(lcd_line, "Humidity:    %" PRId32 "%%", hum_raw);
        display.print(lcd_line);
        ThisThread::sleep_for(1000ms);
    }
}

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

int sht40_temp_conversion(uint16_t temp_ticks, uint8_t crc){
    int t_degC = 0;
    t_degC = -49 + 315 * temp_ticks/65535;  // Fahrenheit conversion.
    return t_degC;
}

int sht40_hum_conversion(uint16_t rh_ticks, uint8_t crc){
    int rh_pRH = 0;
    rh_pRH = -6 + 125 * rh_ticks/65535;
    if (rh_pRH > 100){rh_pRH = 100;}
    if (rh_pRH < 0){rh_pRH = 0;}
    return rh_pRH;
}

int sh40_read(I2C& i2c, int32_t& temperature, int32_t& humidity){
    int i2c_result = 0;
    char command[1] = {SHT4X_CMD_MEASURE_HPM};
    char data[6];
    i2c_result = i2c.write(SHT40AD1B_I2C_ADDR, command, 1);
    if (i2c_result > 0){
        printf("Failure in I2C command write: Code=%i\n", i2c_result);
        return i2c_result;
    }
    ThisThread::sleep_for(100ms);
    i2c_result = i2c.read(SHT40AD1B_I2C_ADDR, data, 6);
    if (i2c_result > 0){
        printf("Failure in I2C HPM Read: Code=%i\n", i2c_result);
        return i2c_result;
    }
    // temperature data
    uint16_t t_ticks = data[0] * 256 + data[1];
    uint8_t checksum_t = data[2];
    // Relative humidity data
    uint16_t rh_ticks = data[3] * 256 + data[4];
    uint8_t checksum_rh = data[5];

    temperature = sht40_temp_conversion(t_ticks, checksum_t);
    humidity = sht40_hum_conversion(rh_ticks, checksum_rh);
    printf("Read successful: temp=%" PRId32 "F\thumidity=%" PRId32 "\n", temp_raw, hum_raw);
    return i2c_result;
}