#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "command.h"
#include "led.h"
#include "pwm_driver.h"
#include "hardware/pwm.h"

extern pwm_t pwm;  // access global PWM instance from main.c

void command_handle(const char *raw_input) {
    char input[64];
    strncpy(input, raw_input, sizeof(input));
    input[sizeof(input) - 1] = '\0';

    // Convert to lowercase
    for (int i = 0; input[i]; i++) {
        input[i] = tolower((unsigned char)input[i]);
    }

    // Parse PWM command
    if (strncmp(input, "pwm ", 4) == 0) {
        char *subcommand = strtok(input + 4, " ");
        char *value_str = strtok(NULL, " ");

        if (!subcommand || !value_str) {
            printf("\n❌ Usage: pwm <duty|freq> <value>\n");
            return;
        }

        if (strcmp(subcommand, "duty") == 0) {
            float duty = atof(value_str);
            if (duty < 0.0f || duty > 100.0f) {
                printf("\n❌ Duty must be 0–100\n");
            } else {
                pwm_driver_set_duty(&pwm, duty);
                printf("\n✅ PWM duty set to %.1f%%\n", duty);
            }
        } else if (strcmp(subcommand, "freq") == 0) {
            int freq = atoi(value_str);
            if (freq <= 0) {
                printf("\n❌ Frequency must be positive\n");
            } else {
                pwm_driver_set_freq(&pwm, (uint32_t)freq);

                // Compute true frequency after wrap adjustment
                uint32_t actual_wrap = pwm.wrap;
                float actual_freq = (float)SYS_CLK_HZ / (float)actual_wrap;

                printf("\n✅ PWM frequency set to ~%.2f Hz (wrap = %u)\n", actual_freq, actual_wrap);
            }
        } else {
            printf("\n❌ Unknown PWM command: %s\n", subcommand);
        }

        fflush(stdout);
        return;
    }

    // LED control commands
    if (strcmp(input, "on") == 0) {
        led_set_mode(LED_MODE_MANUAL_ON);
    } else if (strcmp(input, "off") == 0) {
        led_set_mode(LED_MODE_MANUAL_OFF);
    } else if (strcmp(input, "toggle") == 0) {
        led_set_mode(LED_MODE_TOGGLE);
    } else if (strcmp(input, "auto") == 0) {
        led_set_mode(LED_MODE_AUTO);
    } else {
        printf("\n❌ Unknown command: %s\n", input);
        printf("Available: on, off, toggle, auto, pwm duty <0-100>, pwm freq <hz>\n");
        fflush(stdout);
        return;
    }

    // Echo LED status
    printf("\n🔁 %s — %s\n", input, led_status_str());
    fflush(stdout);
}
