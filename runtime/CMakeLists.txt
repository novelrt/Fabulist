include(GenerateExportHeader)

add_library(runtime
    story.cpp
)

set(public_headers
    include/fabulist/runtime/story.hpp
)

generate_export_header(runtime
    PREFIX_NAME FABULIST_
    EXPORT_FILE_NAME fabulist_runtime_export.hpp
)

set_target_properties(runtime
    PROPERTIES
        OUTPUT_NAME fabulist-runtime
        PUBLIC_HEADER "${public_headers};${CMAKE_CURRENT_BINARY_DIR}/fabulist_export.hpp"
)

target_compile_features(runtime
    PUBLIC
        cxx_std_17
)

target_include_directories(runtime
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include_private>
)

target_link_libraries(runtime
    PUBLIC
        lua::lua
)

install(
    TARGETS runtime
    EXPORT fabulist
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/fabulist/runtime
)
