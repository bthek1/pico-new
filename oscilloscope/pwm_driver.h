#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

#include <stdbool.h>
#include <stdint.h>  // ✅ Required for uint32_t and uint16_t


typedef struct {
    uint32_t gpio;
    uint32_t slice;
    uint32_t channel;
    uint16_t wrap;
} pwm_t;

bool pwm_driver_init(pwm_t *pwm, uint32_t gpio, uint32_t freq_hz);
void pwm_driver_set_duty(pwm_t *pwm, float duty_percent);
void pwm_driver_enable(pwm_t *pwm, bool enabled);
void pwm_driver_set_freq(pwm_t *pwm, uint32_t freq_hz);
float pwm_driver_get_duty(const pwm_t *pwm);

#endif
