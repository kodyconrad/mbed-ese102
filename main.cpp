#include "mbed.h"

UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX);
PwmOut pwm(LED1);

int main() {
    printf("Mbed OS %d.%d.%d\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    // Set intial PWM frequency and duty cycle
    pwm.period(0.01);
    pwm.write(0.0);

    float pulse_step = 0.05;
    std::chrono::milliseconds duration(50);

    while (1) {
        // Increase duty cycle to 90%
        for (float i = 0.0; i < .90; i += pulse_step)
        {
            pwm.write(i);
            ThisThread::sleep_for(duration);
        }

        // Decrease duty cycle to 0%
        for (float i = .90; i > 0.0; i -= pulse_step)
        {
            pwm.write(i);
            ThisThread::sleep_for(duration);
        }
    }
}
