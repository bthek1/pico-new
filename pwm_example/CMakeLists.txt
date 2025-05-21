add_executable(pwm_example
    main.c
)

# Link standard Pico libraries and PWM hardware support
target_link_libraries(pwm_example
    pico_stdlib
    hardware_pwm
)

# Optional: Enable USB stdio (disable UART if not needed)
pico_enable_stdio_usb(pwm_example 1)
pico_enable_stdio_uart(pwm_example 0)

# Generate .uf2, .bin, .elf
pico_add_extra_outputs(pwm_example)
