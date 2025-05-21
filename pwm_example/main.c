#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PWM_PIN 15

int main() {
    stdio_init_all();

    // Set GPIO function to PWM
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to the pin
    uint slice_num = pwm_gpio_to_slice_num(PWM_PIN);

    // Set period: PWM wraps at 65535 (16-bit counter)
    pwm_set_wrap(slice_num, 65535);

    // Set duty cycle (initial)
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(PWM_PIN), 0);

    // Enable PWM slice
    pwm_set_enabled(slice_num, true);

    // Gradually increase duty cycle to fade LED
    while (true) {
        for (uint16_t level = 0; level < 65535; level += 512) {
            pwm_set_chan_level(slice_num, pwm_gpio_to_channel(PWM_PIN), level);
            sleep_ms(5);
        }
        for (uint16_t level = 65535; level > 0; level -= 512) {
            pwm_set_chan_level(slice_num, pwm_gpio_to_channel(PWM_PIN), level);
            sleep_ms(5);
        }
    }
}
