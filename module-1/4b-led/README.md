# Single Shift Register LED Control

This application introduces the use of a single [SN74HC595](https://www.ti.com/product/SN74HC595) to 1 or more LED's to test your understandingbefore moving on to LCD control.

## Connections & References

**Note:** This code was tested and adapted before the introduction of the X-Nucleo expansion board and the **SPI3** pins were used due to there proximity to the **3v3** and **GND** pins.

**References**:

- [Nucleo F746ZG Board Pinout](https://os.mbed.com/platforms/ST-Nucleo-F746ZG/#board-pinout)

**Pins**:

- **SPI**, SPI3_SCK (PC_10), MISO (PC_11), MOSI (PC_12), CS (PD_2)

