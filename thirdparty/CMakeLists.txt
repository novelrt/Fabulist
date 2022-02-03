include(CMakeDependentOption)

cmake_dependent_option(FABULIST_THIRDPARTY_JSON "Use vendored JSON library" ON
    "FABULIST_THIRDPARTY" OFF)

if(FABULIST_THIRDPARTY_JSON)
    add_subdirectory(json)
endif()

add_subdirectory(lua)
