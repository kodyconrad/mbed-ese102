#include "main.hxx"

PwmOut led1(LED1);
Mutex lcd_mutex;
Thread ambient_light_thread;
Thread temp_thread;
Thread led_thread;

void read_ambient_light()
{
    char lcd_line[MAX_LCD_LINE];
    while (1)
    {
        lcd_mutex.lock();
        light_percent_value = lcd_ambient_light_sensor.read();
        lcd_backlight.write(light_percent_value);
        printf("Ambient Light: %d%%\n", int(light_percent_value*100));
        sprintf(lcd_line, "Ambient Light: %d%%", int(light_percent_value*100));
        lcd.print(lcd_line, 0x14);
        lcd_mutex.unlock();
        ThisThread::sleep_for(500ms);
    }
}

void update_temp(){
    char lcd_line[MAX_LCD_LINE];
    int32_t temp_raw = 0, hum_raw = 0;
    while(1){
        lcd_mutex.lock();
        lcd.return_home();
        read_sht40(stm_i2c_bus, temp_raw, hum_raw);
        sprintf(lcd_line, "Temperature: %" PRId32 "F", temp_raw);
        lcd.print(lcd_line);
        sprintf(lcd_line, "Humidity:    %" PRId32 "%%", hum_raw);
        lcd.print(lcd_line, 0x40);
        lcd_mutex.unlock();
        ThisThread::sleep_for(1000ms);
    }
}


void led_status_gr(){
    chrono::milliseconds step_delay = 10ms;
    led1.period(BACKLIGHT_PERIOD);
    led1.write(0.0);
    while(1) {
        for (float i = 0; i < 1; i += 0.01)
        {
            led1.write(i);
            ThisThread::sleep_for(step_delay);
        }
        for (float i = 1; i > 0; i -= 0.01)
        {
            led1.write(i);
            ThisThread::sleep_for(step_delay);
        }
    }
}


int main()
{
    // Setup peripherals.
    setup();

    // Start Threads
    ambient_light_thread.start(callback(read_ambient_light));
    temp_thread.start(callback(update_temp));
    led_thread.start(callback(led_status_gr));

    while (1)
    {
        __WFI();
    }
}


void setup(){
    // LCD Character string
    printf("\n## ARM ESE102 - Module 1: Bonus Cascaded LCD Control (MBED Version: %d.%d.%d)##\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    // Backlight configure
    lcd_backlight.period(BACKLIGHT_PERIOD);
    lcd_backlight.write(light_percent_value);
    printf("[Configuration] Backlight configured.");

    // LCD Serial channel configure.
    lcd_spi.format(LCD_SPI_DATA_BIT_COUNT, LCD_SPI_MODE); // Set up the SPI for 16 bit data (due to cascaded shift registers), mode 0.
    lcd_spi.frequency(LCD_SPI_CLOCK);                     // Clock frequency is 1MHz
    lcd_cs = 1;
    printf("[Configuration] Serial channel configured.\n");

    // Initialize display.
    lcd.initialize();
    lcd.clear();
    lcd.print("Temperature & ");
    lcd.command(0xC0);
    lcd.print("     Humidity");
    printf("[Configuration] Display initialized and cleared.\n");
}
