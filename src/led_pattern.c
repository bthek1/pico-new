#include "led_pattern.h"
#include "led_program.h"
#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static rgb_t hue_to_rgb(uint16_t hue, float brightness) {
    hue = hue % 360;
    uint8_t r, g, b;
    uint8_t region = hue / 60;
    uint8_t remainder = (hue % 60) * 255 / 60;

    switch (region) {
        case 0: r = 255; g = remainder; b = 0; break;
        case 1: r = 255 - remainder; g = 255; b = 0; break;
        case 2: r = 0; g = 255; b = remainder; break;
        case 3: r = 0; g = 255 - remainder; b = 255; break;
        case 4: r = remainder; g = 0; b = 255; break;
        default: r = 255; g = 0; b = 255 - remainder; break;
    }

    r = (uint8_t)(r * brightness);
    g = (uint8_t)(g * brightness);
    b = (uint8_t)(b * brightness);

    return (rgb_t){r, g, b};
}

// ---- Pattern implementations ----

static void pattern_rainbow(uint32_t led_count) {
    static int base_hue = 0;
    for (uint32_t i = 0; i < led_count; i++) {
        uint16_t hue = (base_hue + i * 360 / led_count) % 360;
        rgb_t color = hue_to_rgb(hue, 0.2f);
        program_led_set_rgb(i, color);
    }
    program_led_show();
    base_hue = (base_hue + 1) % 360;
}

static void pattern_comet(uint32_t led_count) {
    static int frame = 0;
    static uint16_t comet_hues[3]; // Store a hue per comet
    const int tail_length = 10;
    const int comet_count = 3;

    // Initialize hues once
    static bool initialized = false;
    if (!initialized) {
        for (int i = 0; i < comet_count; i++) {
            comet_hues[i] = rand() % 360;
        }
        initialized = true;
    }

    // Distance between each comet's head
    const int spacing = led_count / comet_count;

    program_led_clear();

    for (int comet = 0; comet < comet_count; comet++) {
        int comet_head = (frame + comet * spacing) % led_count;

        for (int i = 0; i < tail_length; i++) {
            int pos = (comet_head - i + led_count) % led_count;
            float brightness = 0.2f * (1.0f - (float)i / tail_length);

            rgb_t color = hue_to_rgb(comet_hues[comet], brightness);
            program_led_set_rgb(pos, color);
        }
    }

    program_led_show();
    frame = (frame + 1) % led_count;
}


static void pattern_wave(uint32_t led_count) {
    static float phase = 0.0f;

    for (uint32_t i = 0; i < led_count; i++) {
        float x = (float)i / led_count * 2 * M_PI;
        float wave = (sinf(x + phase) + 1.0f) * 0.5f; // 0.0 to 1.0
        float brightness = 0.1f + 0.1f * wave;        // 0.1 to 0.2

        // Vary hue across strip and over time
        uint16_t hue = (uint16_t)((i * 360 / led_count + (int)(phase * 180 / M_PI)) % 360);

        rgb_t color = hue_to_rgb(hue, brightness);
        program_led_set_rgb(i, color);
    }

    program_led_show();

    phase += 0.15f;
    if (phase > 2 * M_PI) phase -= 2 * M_PI;
}

static void pattern_sparkle(uint32_t led_count) {
    program_led_clear();
    for (int i = 0; i < 10; i++) {  // show 10 sparkles at a time
        int index = rand() % led_count;
        uint16_t hue = rand() % 360;
        rgb_t color = hue_to_rgb(hue, 0.2f);
        program_led_set_rgb(index, color);
    }
    program_led_show();
}

static void pattern_pulse(uint32_t led_count) {
    static int frame = 0;
    float brightness = 0.2f * (sinf(frame * 0.1f) * 0.5f + 0.5f);  // 0–0.2
    rgb_t color = { (uint8_t)(255 * brightness), (uint8_t)(0), (uint8_t)(255 * brightness) };
    for (uint32_t i = 0; i < led_count; i++) {
        program_led_set_rgb(i, color);
    }
    program_led_show();
    frame++;
}

// Add more patterns here and register them below

typedef void (*pattern_fn)(uint32_t count);
static pattern_fn patterns[] = {
    pattern_rainbow,
    pattern_comet,
    pattern_wave,
    pattern_sparkle,
    pattern_pulse,
};

static int current_pattern = 0;

void run_current_pattern(uint32_t led_count) {
    patterns[current_pattern](led_count);
}

void advance_pattern() {
    current_pattern = (current_pattern + 1) % (sizeof(patterns) / sizeof(patterns[0]));
}
