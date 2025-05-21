// main.c
#include "pico/stdlib.h"
#include "../src/led.h"
#include "../src/pwm_driver.h"
#include "../src/serial.h"
#include "../src/command.h"
#include <stdio.h>
#include "../src/led_program.h"
#include "../src/led_pattern.h"

#define LED_COUNT (5 * 60)

pwm_t pwm;  // Global PWM instance

int main() {
    stdio_init_all();
    printf("\n🔌 System booting with default settings...\n");

    led_init();

    if (!pwm_driver_init(&pwm, 15, 1000)) {
        printf("❌ Failed to initialize PWM on GPIO 15\n");
        return 1;
    }
    pwm_driver_set_duty(&pwm, 50.0f);

    serial_init();

    bool led_ready = false;
    if (!program_led_init(16, LED_COUNT, false)) {
        printf("❌ Failed to initialize WS2812 LED on GPIO 16\n");
    } else {
        led_ready = true;
    }

    uint32_t last_pattern_time = to_ms_since_boot(get_absolute_time());
    const uint32_t pattern_duration_ms = 10000;

    while (true) {
        led_update();

        if (led_ready) {
            run_current_pattern(LED_COUNT);

            uint32_t now = to_ms_since_boot(get_absolute_time());
            if (now - last_pattern_time >= pattern_duration_ms) {
                advance_pattern();
                last_pattern_time = now;
                printf("🌀 Switched to next pattern\n");
            }
        }

        if (stdio_usb_connected()) {
            serial_poll();
        }

        sleep_ms(20);
    }

    return 0;
}
