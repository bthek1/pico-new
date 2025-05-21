add_executable(project_a
    main.c
)

target_link_libraries(project_a pico_stdlib)

pico_add_extra_outputs(project_a)
