# Copyright 2023 Squalr. Inc.

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Squally VERSION 1.2.2 LANGUAGES C CXX)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# When building with MSVC from a plain shell (without VsDevCmd), INCLUDE/LIB can be
# empty and CL/LINK cannot find the STL/CRT or Windows SDK headers/libraries.
if(WIN32 AND MSVC)
    set(_fallback_include_dirs)
    set(_fallback_library_dirs)

    if("$ENV{INCLUDE}" STREQUAL "" OR "$ENV{LIB}" STREQUAL "")
        get_filename_component(_msvc_bin_dir "${CMAKE_CXX_COMPILER}" DIRECTORY)
        get_filename_component(_msvc_target_arch_dir "${_msvc_bin_dir}" NAME)
        get_filename_component(_msvc_host_arch_dir "${_msvc_bin_dir}" DIRECTORY)
        get_filename_component(_msvc_tools_bin_dir "${_msvc_host_arch_dir}" DIRECTORY)
        get_filename_component(_msvc_root_dir "${_msvc_tools_bin_dir}" DIRECTORY)

        set(_msvc_include_dir "${_msvc_root_dir}/include")
        if(EXISTS "${_msvc_include_dir}")
            list(APPEND _fallback_include_dirs "${_msvc_include_dir}")
        endif()

        set(_msvc_lib_dir "${_msvc_root_dir}/lib/${_msvc_target_arch_dir}")
        if(EXISTS "${_msvc_lib_dir}")
            list(APPEND _fallback_library_dirs "${_msvc_lib_dir}")
        endif()

        get_filename_component(_program_files_x86_dir "${_msvc_root_dir}/../../../../../../.." ABSOLUTE)
        set(_winsdk_include_root "${_program_files_x86_dir}/Windows Kits/10/Include")
        set(_winsdk_lib_root "${_program_files_x86_dir}/Windows Kits/10/Lib")
        set(_winsdk_version "")

        if(EXISTS "${_winsdk_include_root}")
            file(GLOB _winsdk_versions RELATIVE "${_winsdk_include_root}" "${_winsdk_include_root}/*")
            if(_winsdk_versions)
                list(SORT _winsdk_versions)
                list(REVERSE _winsdk_versions)
                list(GET _winsdk_versions 0 _winsdk_version)
            endif()
        endif()

        if(NOT "${_winsdk_version}" STREQUAL "")
            foreach(_sdk_include_subdir ucrt um shared winrt cppwinrt)
                set(_sdk_include_path "${_winsdk_include_root}/${_winsdk_version}/${_sdk_include_subdir}")
                if(EXISTS "${_sdk_include_path}")
                    list(APPEND _fallback_include_dirs "${_sdk_include_path}")
                endif()
            endforeach()

            foreach(_sdk_lib_subdir ucrt um)
                set(_sdk_lib_path "${_winsdk_lib_root}/${_winsdk_version}/${_sdk_lib_subdir}/${_msvc_target_arch_dir}")
                if(EXISTS "${_sdk_lib_path}")
                    list(APPEND _fallback_library_dirs "${_sdk_lib_path}")
                endif()
            endforeach()
        endif()
    endif()

    if(_fallback_include_dirs)
        list(REMOVE_DUPLICATES _fallback_include_dirs)
        include_directories(SYSTEM ${_fallback_include_dirs})
        message(STATUS "MSVC fallback include dirs enabled (${_fallback_include_dirs})")
    endif()

    if(_fallback_library_dirs)
        list(REMOVE_DUPLICATES _fallback_library_dirs)
        link_directories(${_fallback_library_dirs})
        message(STATUS "MSVC fallback library dirs enabled (${_fallback_library_dirs})")
    endif()
endif()

find_package(SteamWorks REQUIRED)

###############################################################################
###############################################################################

# Fix tinyxml2 relwithdebinfo configuration (chooses debug instead of release for relwithdebinfo)
# set_target_properties(tinyxml2::tinyxml2 PROPERTIES
#     MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE
# )

# Bundled Dependencies
add_subdirectory(${PROJECT_SOURCE_DIR}/Source/Engine)

# Capture configuration to header
configure_file(
    ${PROJECT_SOURCE_DIR}/Source/Config.h.in 
    ${CMAKE_BINARY_DIR}/Generated/Config.h
)

# Sources
add_subdirectory(${PROJECT_SOURCE_DIR}/Source)
