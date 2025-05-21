add_executable(main_project
    main.c
)

target_link_libraries(main_project pico_stdlib)

pico_add_extra_outputs(main_project)


# ✅ Ensure USB stdio is enabled
pico_enable_stdio_usb(main_project 1)
pico_enable_stdio_uart(main_project 0)