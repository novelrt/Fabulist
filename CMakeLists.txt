cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

add_subdirectory(thirdparty)

project(Fabulist
    VERSION 0.1.0
    DESCRIPTION "A simple, embeddable scripting language for visual novels"
    HOMEPAGE_URL "https://github.com/novelrt/fabulist"
    LANGUAGES CXX
)

add_subdirectory(src)
add_subdirectory(cli)
