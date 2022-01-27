cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(Fabulist
    VERSION 0.1.0
    DESCRIPTION "A simple, embeddable scripting language for visual novels"
    HOMEPAGE_URL "https://github.com/novelrt/fabulist"
    LANGUAGES C CXX
)

option(FABULIST_THIRDPARTY "Use vendored third-party dependencies" ON)
option(FABULIST_COMPILER "Build compiler" ON)
option(FABULIST_RUNTIME "Build runtime" ON)
option(FABULIST_SAMPLES "Build samples" OFF)

if(FABULIST_THIRDPARTY)
    add_subdirectory(thirdparty)
endif()

if(FABULIST_COMPILER)
    add_subdirectory(compiler)
endif()

if(FABULIST_RUNTIME)
    add_subdirectory(runtime)
endif()

if(FABULIST_SAMPLES)
    add_subdirectory(samples)
endif()

install(
    EXPORT fabulist
    NAMESPACE fabulist::
    DESTINATION lib
)
