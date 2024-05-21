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

std::chrono::milliseconds duration(100);

uint32_t cycle_count = 0;
UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX);
DigitalOut CS(PD_2);
SPI ser_port(PC_12, PC_11, PC_10);

// InterruptIn ser_input(CONSOLE_RX);

void write_sr(SPI &port, DigitalOut &cs, uint16_t data){
    cs=0;
    port.write(data);
    cs=1;
}

int main() {
    printf("\n## ARM ESE102 - Module 1: Cascaded Shift Register (16-bit) LED Example (Mbed Version: %d.%d.%d) ##\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    ser_port.format(16,0);       // Set up the SPI for 16 bit data, //Mode 0 operation
    ser_port.frequency(1000000); // Clock frequency is 1MHz
    uint16_t max_range = 0x8000;
    CS=1;
    write_sr(ser_port, CS, 0x0);
    while (1) {
        for (uint16_t reg = 0xffff; reg > 0; reg--) {
            write_sr(ser_port, CS, reg);
            printf("reg = 0x%04X\n", reg); // Debugging output
            ThisThread::sleep_for(duration);
        }
        cycle_count++;
        printf("Cycle %lu Complete\n", cycle_count);
        ThisThread::sleep_for(duration);
    } 
}
