add_executable({{project_name}}
    main.c
)

target_link_libraries({{project_name}} pico_stdlib)

pico_add_extra_outputs({{project_name}})
