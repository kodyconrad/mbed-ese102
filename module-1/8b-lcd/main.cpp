#include "mbed.h"
#include "lcd.h"

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
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX);
DigitalOut lcd_cs(LCD_SPI_CS);
SPI serial_sr_lcd(LCD_SPI_MOSI, LCD_SPI_MISO, LCD_SPI_SCK);
LCD::LCDController display(serial_sr_lcd, lcd_cs);
PwmOut lcd_backlight(LCD_LED_PWM);
static volatile float light_percent_value = 0.0;
static volatile float light_percent_value_scaled = 0.0;
static volatile bool read_sensors = false;


void float_to_parts(double input, uint32_t& integer_part, uint32_t& decimal_part);
float scale_value(float value, float minimum_value_expected, float maximum_value_expected, float target_minimum, float target_maximum);
void update_backlight();
void flip_2();
void flip_3();

int main() {
    uint32_t light_percent_int, light_percent_dec;
    printf("\n## ARM ESE102 - Module 1: Bonus Cascaded LCD Control (MBED Version: %d.%d.%d)##\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    led1 = 1;
    led2 = 1;
    led3 = 1;
    printf("[Configuration] LED Initial values configured.\n");
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
    printf("[Configuration] Display initialized and cleared.\n");

    // Attach interrupts, tickers, etc.
    led2_flasher.attach(&flip_2, 400ms); // the address of the function to be attached (flip) and the interval (400ms)
    printf("[Configuration] LED 2 flasher attached.\n");
    led3_flasher.attach(&flip_3, 800ms); // the address of the function to be attached (flip) and the interval (800ms)
    printf("[Configuration] LED 3 flasher attached.\n");
    analog_update.attach(&update_backlight, 250ms); // the address of the function to be attached (flip) and the interval (200ms)
    printf("[Configuration] Analog update attached.\n");

    while (1) {
        char formatted_string[40];
        if (read_sensors)
        {
            light_percent_value = light_sensor.read();
            float_to_parts(light_percent_value, light_percent_int, light_percent_dec);
            printf("Light  =  %lu.%lu%%\n", light_percent_int, light_percent_dec);
            sprintf(formatted_string, "Light  =  %lu%%", light_percent_dec);
            display.command(0x2);
            display.print(formatted_string);
            float_to_parts(light_percent_value_scaled, light_percent_int, light_percent_dec);
            printf("Brightness  =  %lu.%lu%%\n", light_percent_int, light_percent_dec);
            sprintf(formatted_string, "Brightness  =  %lu%%", light_percent_dec);
            display.command(0xC0);
            display.print(formatted_string);
        }
        ThisThread::sleep_for(150ms);
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

void update_backlight(){
    led1 = !led1;
    read_sensors = !read_sensors;
    // Values for scaling selected based on lighting in the room to limit minimum and maximum LCD brightness.
    light_percent_value_scaled = 1.0 - scale_value(light_percent_value, 0.0, 1.0, 0.1, .75);
    lcd_backlight.write(light_percent_value_scaled);
}

void flip_2(){
    led2 = !led2;
}

void flip_3(){
    led3 = !led3;
}