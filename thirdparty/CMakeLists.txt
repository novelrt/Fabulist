include(CMakeDependentOption)

cmake_dependent_option(FABULIST_THIRDPARTY_JSON
    "Use vendored JSON library"
    ${FABULIST_DEFAULT_ON}
    "FABULIST_THIRDPARTY"
    OFF
)

if(FABULIST_THIRDPARTY_JSON)
    message(STATUS "Using vendored JSON library")
    add_subdirectory(json)
endif()

add_subdirectory(lua)
