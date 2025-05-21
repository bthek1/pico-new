#ifndef PROGRAM_LED_H
#define PROGRAM_LED_H

#include <stdint.h>
#include <stdbool.h>

// RGB color struct
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_t;

// Initialize the WS2812B LED driver
// gpio_pin: GPIO number the LED data line is connected to
// led_count: number of LEDs in the strip
// is_rgbw: true for RGBW LEDs, false for RGB
bool program_led_init(uint32_t gpio_pin, uint32_t led_count, bool is_rgbw);

// Set the color of a specific LED (0-indexed)
void program_led_set_rgb(uint32_t index, rgb_t color);

// Clear all LEDs (turn off)
void program_led_clear(void);

// Push current buffer to the LED strip
void program_led_show(void);

#endif
