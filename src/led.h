#ifndef LED_H
#define LED_H

#include <stdbool.h>

typedef enum {
    LED_MODE_MANUAL_OFF,
    LED_MODE_MANUAL_ON,
    LED_MODE_TOGGLE,
    LED_MODE_AUTO
} led_mode_t;

void led_init();
void led_update();
void led_set_mode(led_mode_t mode);
led_mode_t led_get_mode();
bool led_is_on();
const char* led_status_str();

#endif
