include(CheckCXXSymbolExists)

check_cxx_symbol_exists(getopt "getopt.h" HAVE_GETOPT)
check_cxx_symbol_exists(getopt_long "getopt.h" HAVE_GETOPT_LONG)

add_executable(cli
    # console output utilities
    console.cpp
    $<$<BOOL:${HAVE_GETOPT}>:console/parse_getopt.cpp>
    $<$<PLATFORM_ID:Windows>:console/parse_win32.cpp>

    # main entry point
    main.cpp
)

target_link_libraries(cli
    PUBLIC
        runtime
)

target_compile_definitions(cli
    PRIVATE
        $<$<BOOL:${HAVE_GETOPT_LONG}>:HAVE_GETOPT_LONG>
        $<$<BOOL:${HAVE_GETOPT}>:HAVE_GETOPT>
)
