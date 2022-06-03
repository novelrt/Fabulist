cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

project(Fabulist
    VERSION 0.1.0
    DESCRIPTION "A simple, embeddable scripting language for visual novels"
    HOMEPAGE_URL "https://github.com/novelrt/fabulist"
    LANGUAGES CXX
)

option(FABULIST_ALL_ON "Turn ON all options defaulted to OFF" OFF)
option(FABULIST_ALL_OFF "Turn OFF all options defaulted to ON" OFF)

set(FABULIST_DEFAULT_ON ON)
set(FABULIST_DEFAULT_OFF OFF)

if(FABULIST_ALL_ON)
    set(FABULIST_DEFAULT_ON ON)
    set(FABULIST_DEFAULT_OFF ON)
elseif(FABULIST_ALL_OFF)
    set(FABULIST_DEFAULT_ON OFF)
    set(FABULIST_DEFAULT_OFF OFF)
endif()

if(FABULIST_ALL_ON AND FABULIST_ALL_OFF)
    message(FATAL_ERROR "FABULIST_ALL_ON and FABULIST_ALL_OFF cannot be specified concurrently.")
endif()

option(FABULIST_THIRDPARTY "Use vendored third-party dependencies" ${FABULIST_DEFAULT_ON})
option(FABULIST_COMPILER "Build compiler" ${FABULIST_DEFAULT_ON})
option(FABULIST_RUNTIME "Build runtime" ${FABULIST_DEFAULT_ON})
option(FABULIST_SAMPLES "Build samples" ${FABULIST_DEFAULT_OFF})

add_subdirectory(thirdparty)

if(FABULIST_COMPILER)
    message(STATUS "Building compiler")
    add_subdirectory(compiler)
endif()

if(FABULIST_RUNTIME)
    message(STATUS "Building runtime")
    add_subdirectory(runtime)
endif()

if(FABULIST_SAMPLES)
    message(STATUS "Building samples")
    add_subdirectory(samples)
endif()

install(
    EXPORT fabulist
    NAMESPACE fabulist::
    DESTINATION lib
)
