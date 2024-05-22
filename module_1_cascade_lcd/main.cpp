#include "mbed.h"
#include "lcd.h"

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

std::chrono::milliseconds duration(150);

uint32_t cycle_count = 0;
char buffer[80];
UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX);
static DigitalOut chip_select(PD_2);
SPI serial_sr_lcd(PC_12, PC_11, PC_10);
LCD::LCDController display(serial_sr_lcd, chip_select);


int main() {
    printf("\n## ARM ESE102 - Module 1: Bonus Cascaded LCD Control (MBED Version: %d.%d.%d)##\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    serial_sr_lcd.format(16,0);       // Set up the SPI for 16 bit data, //Mode 0 operation
    serial_sr_lcd.frequency(1000000); // Clock frequency is 1MHz
    chip_select=1;
    display.initialize();
    ThisThread::sleep_for(100ms);
    display.clear();
    while (1) {
        char formatted_string[40];
        for (char character = 0x20; character <= 0x7e; character++){
            sprintf(formatted_string, " %c ", character);
            display.print(formatted_string);
            ThisThread::sleep_for(250ms);
        }
        display.clear();
    }
}
