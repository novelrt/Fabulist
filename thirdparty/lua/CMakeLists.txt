include(CMakeDependentOption)
include(FetchContent)

set(FABULIST_THIRDPARTY_LUA_VERSION "5.1.5" CACHE STRING
    "Fabulist vendored Lua library version")

if(NOT "${FABULIST_THIRDPARTY_LUA_VERSION}" STREQUAL "5.1.5")
    message(WARNING "FABULIST_THIRDPARTY_LUA_VERSION is not currently respected")
endif()

FetchContent_Declare(lua
    URL https://www.lua.org/ftp/lua-5.1.5.tar.gz
    URL_HASH SHA512=0142fefcbd13afcd9b201403592aa60620011cc8e8559d4d2db2f92739d18186860989f48caa45830ff4f99bfc7483287fd3ff3a16d4dec928e2767ce4d542a9

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

FetchContent_GetProperties(lua)
if(NOT lua_POPULATED)
    FetchContent_Populate(lua)
endif()

file(READ "${lua_SOURCE_DIR}/src/Makefile" lua_makefile)

# Parse out object files
string(REGEX REPLACE ".+CORE_O=[\t ]+(.+)[\r\n ]+LIB_O=[\t ]+(.+)[\r\n ]+LUA_T=[\t ]+.+" "\\1;\\2" lua_objects "${lua_makefile}")
string(REGEX REPLACE "[\r\t\n ]+\\\\[\r\t\n ]+" " " lua_objects "${lua_objects}")
string(STRIP "${lua_objects}" lua_objects)
string(REGEX REPLACE "[\r\n ]+" ";" lua_objects "${lua_objects}")

# Parse out source files and headers
string(REGEX REPLACE ".+# DO NOT DELETE[\r\n ]+(.+)#.+" "\\1" lua_sources "${lua_makefile}")
string(REGEX REPLACE "[\r\t\n ]+\\\\[\r\t\n ]+" " " lua_sources "${lua_sources}")
string(STRIP "${lua_sources}" lua_sources)
string(REGEX REPLACE "[\r\n]+" ";" lua_sources "${lua_sources}")
string(REGEX REPLACE "[: ]+" "\\\\;" lua_sources "${lua_sources}")

set(source_files "")
set(header_files "")
foreach(object_sources IN LISTS lua_sources)
    list(GET object_sources 0 object)
    list(GET object_sources 1 source_file)
    list(SUBLIST object_sources 2 -1 header_file_list)
    list(FIND lua_objects "${object}" found)

    if(found GREATER -1)
        list(APPEND source_files "${source_file}")
        list(APPEND header_files ${header_file_list})
    endif()
endforeach()

list(REMOVE_DUPLICATES header_files)

list(TRANSFORM source_files PREPEND "${lua_SOURCE_DIR}/src/")
list(TRANSFORM header_files PREPEND "${lua_SOURCE_DIR}/src/")

add_library(lua ${source_files})
add_library(lua::lua ALIAS lua)
set_target_properties(lua
    PROPERTIES
        OUTPUT_NAME fabulist-lua
)
target_include_directories(lua
    PUBLIC
        $<BUILD_INTERFACE:${lua_SOURCE_DIR}/src>
)

target_compile_options(lua
    PRIVATE
        $<$<C_COMPILER_ID:AppleClang>:-Wno-empty-body>
        $<$<C_COMPILER_ID:Clang>:-Wno-empty-body>
        $<$<C_COMPILER_ID:GNU>:-Wno-empty-body>
        $<$<C_COMPILER_ID:MSVC>:/wd4390> # empty control statement found
)

install(
    TARGETS lua
    EXPORT fabulist
    LIBRARY DESTINATION lib
)
