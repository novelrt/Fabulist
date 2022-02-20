include(CMakeDependentOption)

cmake_dependent_option(FABULIST_COMPILER_CLI
    "Build command-line compiler"
    ${FABULIST_DEFAULT_OFF}
    "FABULIST_COMPILER"
    OFF
)

add_subdirectory(lib)

if(FABULIST_COMPILER_CLI)
    message(STATUS "Building compiler frontend")
    add_subdirectory(cli)
endif()
