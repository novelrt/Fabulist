include(CMakeDependentOption)

cmake_dependent_option(FABULIST_SAMPLE_CLI "Build cli sample" ON
    "FABULIST_SAMPLES;FABULIST_RUNTIME" OFF)

if(FABULIST_SAMPLE_CLI)
    message(WARNING "Fabulist runtime is currently broken - refusing to build cli sample")
    # add_subdirectory(cli)
endif()
