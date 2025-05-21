add_executable(main_project
    main.c
)

target_link_libraries(main_project pico_stdlib)

pico_add_extra_outputs(main_project)
