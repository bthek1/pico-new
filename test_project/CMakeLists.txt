add_executable(test_project
    main.c
)

target_link_libraries(test_project pico_stdlib)

pico_add_extra_outputs(test_project)
