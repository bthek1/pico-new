#include "pico/stdlib.h"
#include <stdio.h>

int main() {
    stdio_init_all();  // ⚠️ Initialize USB stdio

    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    printf("✅ Hello from Raspberry Pi Pico via USB serial!\n");

    while (true) {
        gpio_put(LED_PIN, 1);
        printf("LED ON\n");
        sleep_ms(250);

        gpio_put(LED_PIN, 0);
        printf("LED OFF\n");
        sleep_ms(250);
    }
}
