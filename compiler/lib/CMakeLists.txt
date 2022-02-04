include(GenerateExportHeader)

add_library(compiler
    $<$<AND:$<VERSION_GREATER_EQUAL:${FABULIST_LUA_VERSION},5.1>,$<VERSION_LESS:${FABULIST_LUA_VERSION},5.2>>:compatibility/lua5.1.cpp>

    compiler/convenience.cpp

    compiler/parse.cpp
    compiler/parse/build_error_message.cpp
    compiler/parse/stack_trace.cpp

    compiler/private.cpp
    compiler/save.cpp

    compiler/setup.cpp

    compiler/setup/actions.cpp
    compiler/setup/actions/jump.cpp

    compiler/setup/base.cpp
    compiler/setup/options.cpp
    compiler/setup/section.cpp
    compiler/setup/speaker.cpp

    section/setup.cpp
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
)

target_link_libraries(compiler
    PRIVATE
        nlohmann_json::nlohmann_json
    PUBLIC
        lua::lua
)

install(
    TARGETS compiler
    EXPORT fabulist
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/fabulist/compiler
)
