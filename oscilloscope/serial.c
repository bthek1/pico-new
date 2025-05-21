#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "serial.h"
#include "command.h"

#define MAX_INPUT_LEN 64
static char input[MAX_INPUT_LEN];
static int input_pos = 0;

void serial_init() {
    printf("✅ USB serial ready. Commands: on, off, toggle, auto\n");
    fflush(stdout);
}

void serial_poll() {
    int ch = getchar_timeout_us(0);
    if (ch == PICO_ERROR_TIMEOUT) return;

    if (ch == '\r' || ch == '\n') {
        input[input_pos] = '\0';

        // Pass input to command processor
        command_handle(input);

        input_pos = 0;
    } else if (input_pos < MAX_INPUT_LEN - 1) {
        putchar(ch);
        input[input_pos++] = ch;
        fflush(stdout);
    }
}
