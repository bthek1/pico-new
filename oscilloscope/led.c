#include <stdio.h>
#include "pico/stdlib.h"
#include "led.h"

#define LED_PIN 25
#define TOGGLE_INTERVAL_MS 250

static bool led_on = false;
static led_mode_t mode = LED_MODE_AUTO;
static absolute_time_t next_toggle;

void led_init() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    next_toggle = make_timeout_time_ms(TOGGLE_INTERVAL_MS);
}

void led_update() {
    if (mode == LED_MODE_AUTO && absolute_time_diff_us(get_absolute_time(), next_toggle) <= 0) {
        led_on = !led_on;
        gpio_put(LED_PIN, led_on);
        next_toggle = delayed_by_ms(next_toggle, TOGGLE_INTERVAL_MS);
    } else if (mode == LED_MODE_TOGGLE) {
        led_on = !led_on;
        gpio_put(LED_PIN, led_on);
        mode = led_on ? LED_MODE_MANUAL_ON : LED_MODE_MANUAL_OFF;
    }
}

void led_set_mode(led_mode_t new_mode) {
    mode = new_mode;
    if (mode == LED_MODE_MANUAL_ON) {
        led_on = true;
        gpio_put(LED_PIN, 1);
    } else if (mode == LED_MODE_MANUAL_OFF) {
        led_on = false;
        gpio_put(LED_PIN, 0);
    }
    // toggle and auto modes will be handled in led_update
}

led_mode_t led_get_mode() {
    return mode;
}

bool led_is_on() {
    return led_on;
}

const char* led_status_str() {
    static char status[32];
    const char* mode_str = "";

    switch (mode) {
        case LED_MODE_MANUAL_ON:  mode_str = "MANUAL_ON"; break;
        case LED_MODE_MANUAL_OFF: mode_str = "MANUAL_OFF"; break;
        case LED_MODE_TOGGLE:     mode_str = "TOGGLE"; break;
        case LED_MODE_AUTO:       mode_str = "AUTO"; break;
    }

    snprintf(status, sizeof(status), "%s (LED %s)", mode_str, led_on ? "ON" : "OFF");
    return status;
}
