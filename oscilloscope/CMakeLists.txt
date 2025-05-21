add_executable(oscilloscope
    main.c
)

target_link_libraries(oscilloscope pico_stdlib)

pico_add_extra_outputs(oscilloscope)
