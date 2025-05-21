add_executable({{project_name}}
    main.c
)

# Link standard Pico libraries and PWM hardware support
target_link_libraries({{project_name}}
    pico_stdlib
    hardware_pwm
)

# Optional: Enable USB stdio (disable UART if not needed)
pico_enable_stdio_usb({{project_name}} 1)
pico_enable_stdio_uart({{project_name}} 0)

# Generate .uf2, .bin, .elf
pico_add_extra_outputs({{project_name}})
