include(CheckCXXSymbolExists)

check_cxx_symbol_exists(getopt "getopt.h" HAVE_GETOPT)
check_cxx_symbol_exists(getopt_long "getopt.h" HAVE_GETOPT_LONG)

add_executable(compiler_cli
    # console output utilities
    console.cpp
    $<$<BOOL:${HAVE_GETOPT}>:console/parse_getopt.cpp>
    $<$<PLATFORM_ID:Windows>:console/parse_win32.cpp>

    # main entry point
    main.cpp
)

target_link_libraries(compiler_cli
    PUBLIC
        compiler
)

target_compile_definitions(compiler_cli
    PRIVATE
        $<$<BOOL:${HAVE_GETOPT_LONG}>:HAVE_GETOPT_LONG>
        $<$<BOOL:${HAVE_GETOPT}>:HAVE_GETOPT>
)

target_compile_options(compiler_cli
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/D_CRT_SECURE_NO_WARNINGS /D_SCL_NO_WARNINGS /D__STDC_WANT_SECURE_LIB__=1> # function or variable may be unsafe
        $<$<CXX_COMPILER_ID:MSVC>:/wd4464> # relative include path contains '..'
        $<$<CXX_COMPILER_ID:MSVC>:/wd4820> # bytes padding after data member
        $<$<CXX_COMPILER_ID:MSVC>:/wd5045> # compiler will insert spectre mitigation for memory load
        $<$<CXX_COMPILER_ID:MSVC>:/wd4623> # default constructor was implicitly defined as deleted
        $<$<CXX_COMPILER_ID:MSVC>:/wd4625> # copy constructor was implicitly defined as deleted
        $<$<CXX_COMPILER_ID:MSVC>:/wd4626> # assignment operator was implicitly defined as deleted
        $<$<CXX_COMPILER_ID:MSVC>:/wd5026> # move constructor was implicitly defined as deleted
        $<$<CXX_COMPILER_ID:MSVC>:/wd5027> # move assignment operator was implicitly defined as deleted
)

install(
    TARGETS compiler_cli
    RUNTIME DESTINATION bin
)
