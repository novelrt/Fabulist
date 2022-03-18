include(CMakeDependentOption)

cmake_dependent_option(FABULIST_SAMPLE_CLI
    "Build cli sample"
    ${FABULIST_DEFAULT_ON}
    "FABULIST_SAMPLES;FABULIST_RUNTIME"
    OFF
)

if(FABULIST_SAMPLE_CLI)
    message(STATUS "Building cli sample")
    add_subdirectory(cli)
endif()
