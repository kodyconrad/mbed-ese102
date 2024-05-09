#include "mbed.h"

UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX);
PwmOut pwm(LED1);

int main() {
    printf("Mbed OS %d.%d.%d\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    // Set the PWM frequency and duty cycle
    pwm.period(0.01); // 100 Hz frequency
    pwm.write(0.5);   // 50% duty cycle

    std::chrono::milliseconds duration(100);

    while (1) {
        // Increase duty cycle to 75%
        for (float i = 0.0; i < .90; i += 0.1)
        {
            pwm.write(i);
            ThisThread::sleep_for(duration);
        }

        for (float i = .90; i > 0.0; i -= 0.1)
        {
            pwm.write(i);
            ThisThread::sleep_for(duration);
        }
    }
}
