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
    include/fabulist/compiler/section.hpp
)

generate_export_header(compiler
    PREFIX_NAME FABULIST_
    EXPORT_FILE_NAME fabulist_compiler_export.hpp
)

list(APPEND public_headers ${CMAKE_CURRENT_BINARY_DIR}/fabulist_compiler_export.hpp)

set_target_properties(compiler
    PROPERTIES
        OUTPUT_NAME fabulist-compiler-$<CONFIG>
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

target_compile_options(compiler
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/D_CRT_SECURE_NO_WARNINGS /D_SCL_NO_WARNINGS /D__STDC_WANT_SECURE_LIB__=1> # function or variable may be unsafe
        $<$<CXX_COMPILER_ID:MSVC>:/wd4464> # relative include path contains '..'
        $<$<CXX_COMPILER_ID:MSVC>:/wd4820> # bytes padding after data member
        $<$<CXX_COMPILER_ID:MSVC>:/wd5045> # compiler will insert spectre mitigation for memory load
        $<$<CXX_COMPILER_ID:MSVC>:/wd4623> # default constructor was implicitly defined as deleted
        $<$<CXX_COMPILER_ID:MSVC>:/wd4626> # assignment operator was implicitly defined as deleted
        $<$<CXX_COMPILER_ID:MSVC>:/wd5027> # move assignment operator was implicitly defined as deleted
)

install(
    TARGETS compiler
    EXPORT fabulist
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/fabulist/compiler
)
