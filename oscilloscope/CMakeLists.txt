add_executable(oscilloscope
    main.c
    ../src/led.c
    ../src/pwm_driver.c
    ../src/serial.c
    ../src/command.c
    ../src/led_program.c
    ../src/led_pattern.c
)

# 👇 Correct: point to the actual .pio file path
pico_generate_pio_header(oscilloscope
    ${CMAKE_CURRENT_LIST_DIR}/../lib/pico-examples/pio/ws2812/ws2812.pio
)


target_include_directories(oscilloscope PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(oscilloscope
    pico_stdlib
    hardware_pwm
    hardware_pio
)
pico_enable_stdio_usb(oscilloscope 1)
pico_enable_stdio_uart(oscilloscope 0)

pico_add_extra_outputs(oscilloscope)
