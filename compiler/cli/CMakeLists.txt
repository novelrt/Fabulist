add_executable(compiler_cli main.cpp)

target_link_libraries(compiler_cli
    PUBLIC
        compiler
)

install(
    TARGETS compiler_cli
    RUNTIME DESTINATION bin
)
