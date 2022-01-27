include(CMakeDependentOption)

cmake_dependent_option(FABULIST_SAMPLE_CLI "Build cli sample" ON
    "FABULIST_SAMPLES" ON)

if(FABULIST_SAMPLE_CLI)
    add_subdirectory(cli)
endif()
