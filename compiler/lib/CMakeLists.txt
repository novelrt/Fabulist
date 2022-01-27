include(GenerateExportHeader)

add_library(compiler
    compiler.cpp
)

set(public_headers
    include/fabulist/compiler/compiler.hpp
)

generate_export_header(compiler
    PREFIX_NAME FABULIST_
    EXPORT_FILE_NAME fabulist_compiler_export.hpp
)

set_target_properties(compiler
    PROPERTIES
        OUTPUT_NAME fabulist-compiler
        PUBLIC_HEADER "${public_headers}"
)

target_compile_features(compiler
    PUBLIC
        cxx_std_17
)

target_include_directories(compiler
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
)

target_link_libraries(compiler
    PRIVATE
        sol2::sol2
)

install(
    TARGETS compiler
    EXPORT fabulist
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/fabulist/compiler
)
