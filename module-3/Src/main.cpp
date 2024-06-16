#include "main.hxx"

Mutex ambient_sensor_mutex;
Thread ambient_light_thread;

int main() {
    // LCD Character string
    char lcd_line[MAX_LCD_LINE];
    int32_t temp_raw = 0, hum_raw = 0;
    printf("\n## ARM ESE102 - Module 1: Bonus Cascaded LCD Control (MBED Version: %d.%d.%d)##\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    //Backlight configure
    lcd_backlight.period(BACKLIGHT_PERIOD);
    lcd_backlight.write(light_percent_value);
    printf("[Configuration] Backlight configured.");

    // LCD Serial channel configure.
    lcd_spi.format(LCD_SPI_DATA_BIT_COUNT, LCD_SPI_MODE); // Set up the SPI for 16 bit data (due to cascaded shift registers), mode 0.
    lcd_spi.frequency(LCD_SPI_CLOCK); // Clock frequency is 1MHz
    lcd_cs=1;
    printf("[Configuration] Serial channel configured.\n");

    // Initialize display.
    lcd.initialize();
    lcd.clear();
    lcd.print("Temperature & ");
    lcd.command(0xC0);
    lcd.print("     Humidity");
    printf("[Configuration] Display initialized and cleared.\n");

    // Start Threads
    ambient_light_thread.start(callback(read_ambient_light));

    while (1) {
        lcd.command(0x2);
        read_sht40(stm_i2c_bus, temp_raw, hum_raw);
        sprintf(lcd_line, "Temperature: %" PRId32 "F", temp_raw);
        lcd.print(lcd_line);
        lcd.command(0xC0);
        sprintf(lcd_line, "Humidity:    %" PRId32 "%%", hum_raw);
        lcd.print(lcd_line);
        ThisThread::sleep_for(1000ms);
    }
}

void read_ambient_light() {
    uint32_t light_percent_int = 0, light_percent_dec = 0;
    while(1) {
        ambient_sensor_mutex.lock();
        light_percent_value = lcd_ambient_light_sensor.read();
        float_to_parts(light_percent_value, light_percent_int, light_percent_dec);
        lcd_backlight.write(light_percent_value);
        printf("Percent Value: %lu.%lu\n", light_percent_int,light_percent_dec);
        ambient_sensor_mutex.unlock();
        ThisThread::sleep_for(250ms);
    }
}
