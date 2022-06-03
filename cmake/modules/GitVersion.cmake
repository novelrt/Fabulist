set(all_things
    USE_NAMESPACE
    USE_STD_STRING
    USE_CONSTEXPR
    PREFIX_NAME
    VERSION_FILE_NAME
    NAMESPACE
)

function(extract_git_version prefix)
    find_program(GIT_PROGRAM git)

    if(NOT GIT_PROGRAM)
        set(${prefix}_VERSION_STRING "0.0.0-unknown" PARENT_SCOPE)
        set(${prefix}_VERSION_MAJOR 0 PARENT_SCOPE)
        set(${prefix}_VERSION_MINOR 0 PARENT_SCOPE)
        set(${prefix}_VERSION_PATCH 0 PARENT_SCOPE)
        return()
    endif()

    execute_process(
        COMMAND "${GIT_PROGRAM}" rev-list --tags --max-count=1
        OUTPUT_VARIABLE _git_tag_sha
        RESULT_VARIABLE _git_has_tag
    )

    string(STRIP "${_git_tag_sha}" _git_tag_sha)

    if (NOT ${_git_has_tag} EQUAL 0)
        set(${prefix}_VERSION_STRING "0.0.0-unknown" PARENT_SCOPE)
        set(${prefix}_VERSION_MAJOR 0 PARENT_SCOPE)
        set(${prefix}_VERSION_MINOR 0 PARENT_SCOPE)
        set(${prefix}_VERSION_PATCH 0 PARENT_SCOPE)
        return()
    endif()

    execute_process(
        COMMAND "${GIT_PROGRAM}" describe --tags "${_git_tag_sha}"
        OUTPUT_VARIABLE _git_tag
        RESULT_VARIABLE _git_tag_success
    )
    
    if(NOT _git_tag_success EQUAL 0)
        set(${prefix}_VERSION_STRING "0.0.0-unknown" PARENT_SCOPE)
        set(${prefix}_VERSION_MAJOR 0 PARENT_SCOPE)
        set(${prefix}_VERSION_MINOR 0 PARENT_SCOPE)
        set(${prefix}_VERSION_PATCH 0 PARENT_SCOPE)
        return()
    endif()
    
    execute_process(
        COMMAND "${GIT_PROGRAM}" rev-parse --short HEAD
        OUTPUT_VARIABLE _git_sha
    )
    execute_process(
        COMMAND "${GIT_PROGRAM}" diff-index --quiet --cached HEAD --
        RESULT_VARIABLE _git_staged_changes
    )
    execute_process(
        COMMAND "${GIT_PROGRAM}" diff-files --quiet
        RESULT_VARIABLE _git_unstaged_changes
    )

    string(STRIP "${_git_tag}" _git_tag)
    string(STRIP "${_git_sha}" _git_sha)
    string(REGEX REPLACE [[v?([0-9\.]+)]] "\\1" _git_version "${_git_tag}")
    string(REGEX REPLACE [[([0-9]+)\.[0-9]+\.[0-9]+]] "\\1" _git_version_major "${_git_version}")
    string(REGEX REPLACE [[[0-9]+\.([0-9]+)\.[0-9]+]] "\\1" _git_version_minor "${_git_version}")
    string(REGEX REPLACE [[[0-9]+\.[0-9]+\.([0-9]+)]] "\\1" _git_version_patch "${_git_version}")

    if(${_git_staged_changes} OR ${_git_unstaged_changes})
        set(${prefix}_VERSION_STRING "${_git_version}-dirty+${_git_sha}" PARENT_SCOPE)
    else()
        set(${prefix}_VERSION_STRING "${_git_version}+${_git_sha}" PARENT_SCOPE)
    endif()

    set(${prefix}_VERSION_MAJOR "${_git_version_major}" PARENT_SCOPE)
    set(${prefix}_VERSION_MINOR "${_git_version_minor}" PARENT_SCOPE)
    set(${prefix}_VERSION_PATCH "${_git_version_patch}" PARENT_SCOPE)
endfunction()

function(generate_git_version_header target)
    cmake_parse_arguments(PARSE_ARGV 0 _GVH
        "USE_NAMESPACE;USE_STD_STRING;USE_STD_STRING_VIEW;USE_CONSTEXPR"
        "PREFIX_NAME;VERSION_FILE_NAME;NAMESPACE"
        ""
    )

    if(_GVH_USE_NAMESPACE)
        set(GITVERSION_USE_NAMESPACE 1)
    else()
        set(GITVERSION_USE_NAMESPACE 0)
    endif()

    if(_GVH_USE_STD_STRING)
        set(GITVERSION_USE_STD_STRING 1)
    else()
        set(GITVERSION_USE_STD_STRING 0)
    endif()

    if(_GVH_USE_STD_STRING_VIEW)
        set(GITVERSION_USE_STD_STRING_VIEW 1)
    else()
        set(GITVERSION_USE_STD_STRING_VIEW 0)
    endif()

    if(_GVH_USE_CONSTEXPR)
        set(GITVERSION_USE_CONSTEXPR 1)
    else()
        set(GITVERSION_USE_CONSTEXPR 0)
    endif()

    if(DEFINED _GVH_VERSION_FILE_NAME)
        set(_file_name "${_GVH_VERSION_FILE_NAME}")
    else()
        set(_file_name "git_version.h")
    endif()

    if(_GVH_USE_NAMESPACE AND NOT DEFINED _GVH_NAMESPACE)
        message(FATAL_ERROR "Expected a namespace to be defined if USE_NAMESPACE is set")
    elseif(_GVH_USE_NAMESPACE)
        set(GITVERSION_NAMESPACE "${_GVH_NAMESPACE}")
    endif()

    string(MAKE_C_IDENTIFIER "${_GVH_VERSION_FILE_NAME}" _file_name_identifier)
    string(TOUPPER "${_file_name_identifier}" _file_name_identifier)
    string(MAKE_C_IDENTIFIER "${target}" _target_identifier)
    string(TOUPPER "${_target_identifier}" _target_identifier)
    set(GITVERSION_INCLUDE_GUARD_NAME "${_GVH_PREFIX_NAME}${_target_identifier}_${_file_name_identifier}")

    extract_git_version(GITVERSION)

    get_target_property(_binary_dir ${target} BINARY_DIR)
    configure_file(
        "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/GitVersion/GitVersion.in.h"
        "${_binary_dir}/${_file_name}"
        @ONLY
    )
endfunction()
