include(CMakeDependentOption)


cmake_dependent_option(FABULIST_THIRDPARTY_JSON "Use vendored JSON library" ON
    "FABULIST_THIRDPARTY" OFF)
cmake_dependent_option(FABULIST_THIRDPARTY_LUA "Use vendored Lua library" ON
    "FABULIST_THIRDPARTY" OFF)
cmake_dependent_option(FABULIST_THIRDPARTY_SOL "Use vendored Sol library" ON
    "FABULIST_THIRDPARTY" OFF)

if(FABULIST_THIRDPARTY_JSON)
    add_subdirectory(json)
endif()

if(FABULIST_THIRDPARTY_LUA)
    add_subdirectory(lua)
endif()

if(FABULIST_THIRDPARTY_SOL)
    add_subdirectory(sol)
endif()
