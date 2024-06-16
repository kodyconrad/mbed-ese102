/* lcd.h
Assumes a NHD-0420H1Z-FSW-GBW-33V3 LCD display is being driven by a single or cascaded SNx4HC595 shift register.

Cascaded Configuration:
    - Shift Register #1 is for control, LCD RS == QA, RW == QB, E==QC (Bits 0-2)
    - Shift Register #2 is for data, QA->QH connects to LCD D0-D7 accordingly. (Bits 8-15 )
*/
#ifndef LCD_FILE_H
#define LCD_FILE_H
#include "mbed.h"

namespace LCD {

const uint8_t LINE_CHAR_MAX = 20;

// LCD shift register control bits
const char REGISTER_SELECT_DATA = 1 << 0;
const char RW = 1 << 1;
const char ENABLE = 1 << 2;
const char CONTROL_MASK = REGISTER_SELECT_DATA | RW | ENABLE;

// LCD shift register data bits
const uint16_t LCD_DATA_MASK = 0xff << 8;

// Clears display and sets DDRAM address to "00H" from AC
const char CLEAR_DISPLAY = 1 << 0;

// Sets DDRAM Address to "00H" from AC and returns cursor to its original position if shifted.
const char RETURN_HOME = 1 << 1;

// Sets cursor move direction and specifies display shift.
const char ENTRY_MODE_SET = 1 << 2;
const char ENTRY_MODE_MOVE_RIGHT = 1 << 1;

// Controls the entire display on/off, cursor on/off, and blinking cursor on/off.
const char DISPLAY_ON_OFF_CONTROL = 1 << 3;
const char DISPLAY_ON = 1 << 2;
const char CURSOR_ON = 1 << 1;
const char BLINK_ON = 1 << 0;

// Sets cursor moving and display shift control bit, and the direction without changing DDRAM data.
const char CURSOR_OR_DISPLAY_SHIFT = 1 << 4;
const char CURSOR_SHIFT_LEFT = CURSOR_OR_DISPLAY_SHIFT;
const char CURSOR_SHIFT_RIGHT = CURSOR_OR_DISPLAY_SHIFT | 1 << 2;
const char DISPLAY_LEFT_SHIFT_CURSOR_FOLLOW = CURSOR_OR_DISPLAY_SHIFT | 1 << 3;
const char DISPLAY_RIGHT_SHIFT_CURSOR_FOLLOW = CURSOR_OR_DISPLAY_SHIFT | 1 << 3 | 1 << 2;

// Sets interface data length (DL), number of display lines (N), and character font (F).
const char FUNCTION_SET = 1 << 5;
const char INTERFACE_8BIT = 1 << 4; // 1 == 8 bits, 0 == 4 bits interface.
const char TWO_LINES = 1 << 3; // 1 == 2 lines, 0 == 1 lines
const char FONT_SIZE_LARGE = 1 << 2; // 1 == 5x11, 0 == 5x8

// Sets CGRAM address in address counter.
const char SET_CGRAM_ADDRESS = 1 << 6;

// Sets DDRAM address in address counter.
const char SET_DDRAM_ADDRESS = 1 << 7;

// Reads busy flag (BF) and address counter.
const char READ_BUSY_FLAG_AND_ADDRESS = 1 << 1 | 1 << 0;

// Writes data to internal RAM (DDRAM/CGRAM).
const char WRITE_DATA_TO_RAM = 1 << 0;

// Reads data from internal RAM (DDRAM/CGRAM).
const char READ_DATA_FROM_RAM = 1 << 1 | 1 << 0;


class LCDController {
    /*LCD Controller/Driver class

    * The given SPI instance should be configured for 16 bit, mode 0.
    */
private:
    SPI& spi;
    DigitalOut& cs;

    void shift_out(const uint16_t data) {
        cs = 0;
        this->spi.write(data);
        cs = 1;
    }

public:
    // Constructor that takes an SPI object
    LCDController(SPI& spi, DigitalOut& cs) : spi(spi), cs(cs) {}

    // Clears the LCD display
    void clear(void) {
        command(CLEAR_DISPLAY);
        ThisThread::sleep_for(10ms);
    }

    // Initializes the LCD display
    void initialize(void) {
        /*An internal reset circuit automatically initializes the ST7066U when the power is turned on w/ the following instructions.

        Clear -> Function Set (DL=1, N=0, F=0) -> Display ON/OFF (D=0, C=0, B=0) -> Entry mode (I/D=1, S=0)

        Note, this operation lasts at least 40ms; we do not have read access, so we must rely on delays.

        */
        ThisThread::sleep_for(100ms);
        command(FUNCTION_SET | INTERFACE_8BIT | TWO_LINES | FONT_SIZE_LARGE); //Function set: 8-bit/2-line
        ThisThread::sleep_for(10ms);
        // command(FUNCTION_SET | INTERFACE_8BIT | TWO_LINES); //Function set: 8-bit/2-line
        command(CURSOR_SHIFT_RIGHT); //Set cursor
        ThisThread::sleep_for(10ms);
        command(DISPLAY_ON_OFF_CONTROL | DISPLAY_ON); //Display ON; Cursor ON
        ThisThread::sleep_for(10ms);
        command(ENTRY_MODE_SET); //Entry mode set
        ThisThread::sleep_for(100ms);
    }

    // Prints a string to the LCD display
    void print(const char *string) {
        while (*string) {
            write(*string++);
            wait_us(40);
        }
    }

    // Writes a command to the LCD display
    void write(const char cmd, bool data = true) {
        uint8_t control;
        control = data ? REGISTER_SELECT_DATA | ENABLE : ENABLE;
        uint16_t sr_data = cmd << 8 | control;
        shift_out(sr_data);
        wait_us(5);
        sr_data &= ~ENABLE;
        shift_out(sr_data);
    }

    void command(const char cmd){
        write(cmd, false);
    }
};


} // namespace lcd

#endif // LCD_FILE_H
