#include "led_program.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"
#include <stdlib.h>

static PIO pio_instance = pio0;
static uint sm = 0;
static uint32_t ws2812_pin = 0;
static bool is_rgbw = false;

static rgb_t* color_buf = NULL;
static uint32_t led_count = 0;

bool program_led_init(uint32_t gpio_pin, uint32_t count, bool use_rgbw) {
    if (count == 0) return false;

    ws2812_pin = gpio_pin;
    led_count = count;
    is_rgbw = use_rgbw;

    color_buf = calloc(count, sizeof(rgb_t));
    if (!color_buf) return false;

    uint offset = pio_add_program(pio_instance, &ws2812_program);
    ws2812_program_init(pio_instance, sm, offset, ws2812_pin, 800000, is_rgbw);

    program_led_clear();
    program_led_show();
    return true;
}

void program_led_set_rgb(uint32_t index, rgb_t color) {
    if (index >= led_count || !color_buf) return;
    color_buf[index] = color;
}

void program_led_clear() {
    if (!color_buf) return;
    for (uint32_t i = 0; i < led_count; ++i) {
        color_buf[i] = (rgb_t){0, 0, 0};
    }
}

void program_led_show() {
    if (!color_buf) return;

    for (uint32_t i = 0; i < led_count; ++i) {
        rgb_t c = color_buf[i];
        uint32_t encoded = is_rgbw
            ? ((uint32_t)0 << 24) | ((uint32_t)c.g << 16) | ((uint32_t)c.r << 8) | c.b
            : ((uint32_t)c.g << 16) | ((uint32_t)c.r << 8) | c.b;

        pio_sm_put_blocking(pio_instance, sm, encoded << 8u);
    }
}
