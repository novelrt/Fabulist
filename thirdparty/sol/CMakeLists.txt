include(FetchContent)

if(NOT FABULIST_THIRDPARTY_LUA)
    find_package(Lua REQUIRED)

    if(NOT TARGET lua::lua)
        add_library(lua::lua INTERFACE IMPORTED)
        set_target_properties(lua::lua
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${LUA_INCLUDE_DIR}"
                INTERFACE_LINK_LIBRARIES "${LUA_LIBRARIES}"
        )
    endif()
endif()

FetchContent_Declare(sol2
    URL https://github.com/ThePhD/sol2/archive/refs/tags/v4.0.0-alpha.zip
    URL_HASH SHA512=fa632f7577d031293407e69cb681020a02fdc144c2c6d2be48a1d90995cbdb54f99ab6e0cbd277300449748eb10b16f98d35f84f77e31c990c6d12686662b3f6

    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG v4.0.0-alpha

    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
    STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
    DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
    SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
    INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
    LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"
)

FetchContent_GetProperties(sol2)
if(NOT sol2_POPULATED)
    FetchContent_Populate(sol2)
endif()

add_library(sol2 INTERFACE)
add_library(sol2::sol2 ALIAS sol2)
set_target_properties(sol2 PROPERTIES
    IMPORTED_LOCATION ""
)

target_include_directories(sol2
    INTERFACE
        $<BUILD_INTERFACE:${sol2_SOURCE_DIR}/include>
)

target_link_libraries(sol2
    INTERFACE
        lua::lua
)

get_target_property(incl sol2 INTERFACE_INCLUDE_DIRECTORIES)

install(
    TARGETS sol2
    EXPORT fabulist
)
