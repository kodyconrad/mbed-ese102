#ifndef M3_MAIN_H
#define M3_MAIN_H
#include "mbed.h"
#include "lcd.hxx"
#include "sensiron.hxx"
#include "util.hxx"

std::chrono::milliseconds duration(150);
// List Arduino compatible pins for connection for simultaneous use with IKS4A1
PinName LCD_SPI_SCK = D13;
PinName LCD_SPI_MOSI = D11;
PinName LCD_SPI_MISO = D12;
PinName LCD_SPI_CS = D10;
PinName LCD_LED_PWM = A0;

// I2C bus for sensor control
PinName I2C1_SDA = D14;
PinName I2C1_SCL = D15;
I2C stm_i2c_bus(I2C1_SDA, I2C1_SCL);

UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX);

// LCD Objects and Variables.
AnalogIn lcd_ambient_light_sensor(A1);
DigitalOut lcd_cs(LCD_SPI_CS);
SPI lcd_spi(LCD_SPI_MOSI, LCD_SPI_MISO, LCD_SPI_SCK);
PwmOut lcd_backlight(LCD_LED_PWM);
LCD::LCDController lcd(lcd_spi, lcd_cs);

// LCD Constants
const int LCD_SPI_DATA_BIT_COUNT = 16;
const int LCD_SPI_MODE = 0;
const int LCD_SPI_CLOCK = 1000000;
const int MAX_LCD_LINE = 20;
const float BACKLIGHT_PERIOD = 1.0/120.0;
float light_percent_value = 0.0; // Default to 0% duty (off)

// Prototypes
void read_ambient_light();
void update_backlight();
#endif
