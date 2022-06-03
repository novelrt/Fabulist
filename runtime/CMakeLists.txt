include(GenerateExportHeader)
include(GitVersion)

add_library(runtime
    action.cpp
    actions/jump.cpp
    actions/line.cpp
    actions/options.cpp

    decoder.cpp

    runtime.cpp

    section.cpp
    state.cpp
    story.cpp

    version.cpp
)

set(public_headers
    include/fabulist/runtime/action.hpp

    include/fabulist/runtime/section.hpp
    include/fabulist/runtime/state.hpp
    include/fabulist/runtime/story.hpp

    include/fabulist/runtime/version.hpp
)

generate_export_header(runtime
    PREFIX_NAME FABULIST_
    EXPORT_FILE_NAME fabulist_runtime_export.hpp
)

generate_git_version_header(runtime
    PREFIX_NAME FABULIST_
    NAMESPACE fabulist::runtime
    VERSION_FILE_NAME fabulist_runtime_git_version.hpp
    USE_NAMESPACE USE_STD_STRING_VIEW USE_CONSTEXPR
)

list(APPEND public_headers ${CMAKE_CURRENT_BINARY_DIR}/fabulist_runtime_export.hpp)

set_target_properties(runtime
    PROPERTIES
        OUTPUT_NAME fabulist-runtime-$<CONFIG>
        PUBLIC_HEADER "${public_headers}"
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
    PRIVATE
        nlohmann_json::nlohmann_json
    PUBLIC
        lua::lua
)

install(
    TARGETS runtime
    EXPORT fabulist
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/fabulist/runtime
)
