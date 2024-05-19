#include "mbed.h"
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
UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX);
DigitalOut CS(PD_2);
SPI ser_port(PC_12, PC_11, PC_10);
char red_mask = (0x1 << 1);
char switch_word = 0x10;

void write_sr(SPI &port, DigitalOut &cs, char word){
    cs=0;
    port.write(word);
    cs=1;
}

int main() {
    printf("\n## ARM ESE102 - Part 1: LED Shifting (MBED Version: %d.%d.%d)##\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    ser_port.format(8,0);        // Set up the SPI for 8 bit data, //Mode 0 operation
    ser_port.frequency(1000000); // Clock frequency is 1MHz
    CS=1;
    write_sr(ser_port, CS, 0x0);
    while (1) {
        for (char reg = 1; reg < 0x10; reg++){
            write_sr(ser_port, CS, reg);
            ThisThread::sleep_for(duration);
        }
        write_sr(ser_port, CS, 0x0);
        cycle_count++;
        printf("Cycle Complete: %lu\n", cycle_count);
        ThisThread::sleep_for(duration);
    } 
}
