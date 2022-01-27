include(CMakeDependentOption)

cmake_dependent_option(FABULIST_COMPILER_CLI "Build command-line compiler" OFF
    "FABULIST_COMPILER" OFF)

add_subdirectory(lib)

if(FABULIST_COMPILER_CLI)
    add_subdirectory(cli)
endif()
