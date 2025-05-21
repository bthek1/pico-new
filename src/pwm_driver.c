#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pwm_driver.h"
#include <stdint.h>

bool pwm_driver_init(pwm_t *pwm, uint32_t gpio, uint32_t freq_hz) {
    if (!pwm || freq_hz == 0) return false;

    gpio_set_function(gpio, GPIO_FUNC_PWM);
    pwm->gpio = gpio;
    pwm->slice = pwm_gpio_to_slice_num(gpio);
    pwm->channel = pwm_gpio_to_channel(gpio);

    pwm_driver_set_freq(pwm, freq_hz);
    pwm_driver_enable(pwm, true);
    return true;
}

void pwm_driver_set_freq(pwm_t *pwm, uint32_t freq_hz) {
    if (!pwm || freq_hz == 0) return;

    // Preserve current duty percentage before updating wrap
    float current_duty = pwm_driver_get_duty(pwm);

    // Calculate and clamp wrap
    uint32_t wrap = SYS_CLK_HZ / freq_hz;
    if (wrap > 65535) wrap = 65535;

    pwm->wrap = wrap;
    pwm_set_wrap(pwm->slice, pwm->wrap);

    // Restore duty after wrap change
    pwm_driver_set_duty(pwm, current_duty);
}


void pwm_driver_set_duty(pwm_t *pwm, float duty_percent) {
    if (!pwm || duty_percent < 0.0f || duty_percent > 100.0f) return;
    uint16_t level = (uint16_t)((duty_percent / 100.0f) * pwm->wrap);
    pwm_set_chan_level(pwm->slice, pwm->channel, level);
}

float pwm_driver_get_duty(const pwm_t *pwm) {
    if (!pwm || pwm->wrap == 0) return 0.0f;
    uint16_t level = (pwm->channel == PWM_CHAN_A)
        ? pwm_hw->slice[pwm->slice].cc & 0xFFFF
        : pwm_hw->slice[pwm->slice].cc >> 16;
    return (float)level * 100.0f / pwm->wrap;
}

void pwm_driver_enable(pwm_t *pwm, bool enabled) {
    if (!pwm) return;
    pwm_set_enabled(pwm->slice, enabled);
}
