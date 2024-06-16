#include "mbed.h"
#include "lcd.hxx"
#include "sensiron.hxx"

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

UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX);

// LCD Setup
DigitalOut lcd_cs(LCD_SPI_CS);
SPI serial_sr_lcd(LCD_SPI_MOSI, LCD_SPI_MISO, LCD_SPI_SCK);
LCD::LCDController display(serial_sr_lcd, lcd_cs);
PwmOut lcd_backlight(LCD_LED_PWM);
int32_t temp_raw = 0, hum_raw = 0;
volatile float light_percent_value = 0.25;


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
        read_sht40(stm_i2c_bus, temp_raw, hum_raw);
        sprintf(lcd_line, "Temperature: %" PRId32 "F", temp_raw);
        display.print(lcd_line);
        display.command(0xC0);
        sprintf(lcd_line, "Humidity:    %" PRId32 "%%", hum_raw);
        display.print(lcd_line);
        ThisThread::sleep_for(1000ms);
    }
}
