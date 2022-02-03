include(CMakeDependentOption)
include(FetchContent)

set(lua_versions
    "5.1\;https://www.lua.org/ftp/lua-5.1.5.tar.gz\;SHA512=0142fefcbd13afcd9b201403592aa60620011cc8e8559d4d2db2f92739d18186860989f48caa45830ff4f99bfc7483287fd3ff3a16d4dec928e2767ce4d542a9"
    "5.2\;https://www.lua.org/ftp/lua-5.2.4.tar.gz\;SHA512=cd77148aba4b707b6c159758b5e8444e04f968092eb98f6b4c405b2fb647e709370d5a8dcf604176101d3407e196a7433b5dcdce4fe9605c76191d3649d61a8c"
    "5.3\;https://www.lua.org/ftp/lua-5.3.6.tar.gz\;SHA512=ccc380d5e114d54504de0bfb0321ca25ec325d6ff1bfee44b11870b660762d1a9bf120490c027a0088128b58bb6b5271bbc648400cab84d2dc22b512c4841681"
    "5.4\;https://www.lua.org/ftp/lua-5.4.4.tar.gz\;SHA512=af0c35d5ba00fecbb2dd617bd7b825edf7418a16a73076e04f2a0df58cdbf098dc3ff4402e974afd789eb5d86d2e12ec6df9c84b99b23656ea694a85f83bcd21"
)

set(FABULIST_LUA_VERSION "5.1" CACHE STRING
    "Fabulist vendored Lua library version")

foreach(version IN LISTS lua_versions)
    list(GET version 0 lua_version)
    if(FABULIST_LUA_VERSION VERSION_EQUAL lua_version)
        list(GET version 1 lua_url)
        list(GET version 2 lua_hash)
    endif()
endforeach()

if(NOT lua_url)
    message(FATAL_ERROR "Could not determine URL for building Lua ${FABULIST_LUA_VERSION}")
endif()

FetchContent_Declare(lua
    URL "${lua_url}"
    URL_HASH "${lua_hash}"

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

foreach(file IN LISTS source_files header_files)
    set_property(
        SOURCE "${file}"
        PROPERTY LANGUAGE CXX
    )

    # This is necessary as CMake doesn't automatically pass this flag for
    # whatever reason
    set_property(
        SOURCE "${file}"
        PROPERTY COMPILE_OPTIONS
            "$<$<CXX_COMPILER_ID:AppleClang>:--language=c++>"
            "$<$<CXX_COMPILER_ID:Clang>:--language=c++>"
            "$<$<CXX_COMPILER_ID:GNU>:--language=c++>"
            "$<$<CXX_COMPILER_ID:MSVC>:/Tp>"
    )
endforeach()

add_library(lua ${source_files})
add_library(lua::lua ALIAS lua)
set_target_properties(lua
    PROPERTIES
        OUTPUT_NAME fabulist-lua
        VERSION ${FABULIST_LUA_VERSION}
)
target_include_directories(lua
    PUBLIC
        $<BUILD_INTERFACE:${lua_SOURCE_DIR}/src>
)

target_compile_options(lua
    PRIVATE
        $<$<CXX_COMPILER_ID:AppleClang>:-Wno-empty-body>
        $<$<CXX_COMPILER_ID:Clang>:-Wno-empty-body>
        $<$<CXX_COMPILER_ID:GNU>:-Wno-empty-body>
        $<$<CXX_COMPILER_ID:MSVC>:/wd4390> # empty control statement found

        $<$<CXX_COMPILER_ID:AppleClang>:-Wno-unused-const-variable>
        $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-const-variable>
        $<$<CXX_COMPILER_ID:GNU>:-Wno-unused-const-variable>
        # $<$<CXX_COMPILER_ID:MSVC>:/wd4390> # no msvc error for this?

        $<$<CXX_COMPILER_ID:AppleClang>:-Wno-misleading-indentation>
        $<$<CXX_COMPILER_ID:Clang>:-Wno-misleading-indentation>
        $<$<CXX_COMPILER_ID:GNU>:-Wno-misleading-indentation>
        # $<$<CXX_COMPILER_ID:MSVC>:/wd4390> # no msvc error for this?
)

install(
    TARGETS lua
    EXPORT fabulist
    LIBRARY DESTINATION lib
)
