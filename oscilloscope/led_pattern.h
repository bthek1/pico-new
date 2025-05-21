#ifndef LED_PATTERN_H
#define LED_PATTERN_H

#include <stdint.h>

// Call this every frame to run the current LED pattern
void run_current_pattern(uint32_t led_count);

// Call this to move to the next available pattern
void advance_pattern();

#endif
