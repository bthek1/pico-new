#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    stdio_init_all();  // USB serial init

    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    char input[64];
    int input_pos = 0;
    bool led_on = false;
    bool auto_toggle = true;
    absolute_time_t next_toggle = make_timeout_time_ms(250);

    printf("✅ USB serial ready. Commands: on, off, toggle, auto\n");
    fflush(stdout);  // Force output

    while (true) {
        // Auto toggle every 250ms
        if (auto_toggle && absolute_time_diff_us(get_absolute_time(), next_toggle) <= 0) {
            led_on = !led_on;
            gpio_put(LED_PIN, led_on);
            printf("LED %s\n", led_on ? "ON" : "OFF");
            fflush(stdout);
            next_toggle = delayed_by_ms(next_toggle, 250);
        }

        // Read serial input
        int ch = getchar_timeout_us(0);
        if (ch != PICO_ERROR_TIMEOUT) {
            if (ch == '\r' || ch == '\n') {
                input[input_pos] = '\0';

                // Convert input to lowercase for command handling
                for (int i = 0; i < input_pos; i++) {
                    input[i] = tolower((unsigned char)input[i]);
                }

                // Process command
                if (strcmp(input, "on") == 0) {
                    auto_toggle = false;
                    led_on = true;
                    gpio_put(LED_PIN, 1);
                } else if (strcmp(input, "off") == 0) {
                    auto_toggle = false;
                    led_on = false;
                    gpio_put(LED_PIN, 0);
                } else if (strcmp(input, "toggle") == 0) {
                    auto_toggle = false;
                    led_on = !led_on;
                    gpio_put(LED_PIN, led_on);
                } else if (strcmp(input, "auto") == 0) {
                    auto_toggle = true;
                }

                // Echo command back in uppercase
                printf("🔁 ");
                for (int i = 0; i < input_pos; i++) {
                    putchar(toupper((unsigned char)input[i]));
                }
                printf(" — LED is %s (auto: %s)\n", led_on ? "ON" : "OFF", auto_toggle ? "ON" : "OFF");

                fflush(stdout);
                input_pos = 0;
            } else if (input_pos < (int)(sizeof(input) - 1)) {
                input[input_pos++] = ch;
            }
        }

        sleep_ms(1);
    }
}
