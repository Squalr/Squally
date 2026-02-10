cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

include(FetchContent)

function(strip_cocos_include_prefix target_dir)
    file(GLOB_RECURSE source_files
        "${target_dir}/*.h"
        "${target_dir}/*.hpp"
        "${target_dir}/*.cpp"
        "${target_dir}/*.cxx"
        "${target_dir}/*.cc"
        "${target_dir}/*.c"
    )

    foreach(source_file IN LISTS source_files)
        file(READ "${source_file}" file_contents)
        string(REPLACE "#include \"cocos/" "#include \"" updated_contents "${file_contents}")
        string(REPLACE "#include <cocos/" "#include <" updated_contents "${updated_contents}")

        if(NOT updated_contents STREQUAL file_contents)
            file(WRITE "${source_file}" "${updated_contents}")
        endif()
    endforeach()
endfunction()

# breakpad
FetchContent_Declare(
    breakpad
    GIT_REPOSITORY https://github.com/Squalr/breakpad.git
    GIT_TAG d7a90a8d1648f2e81f51fc3acf9ead7f642d66f4
)
FetchContent_GetProperties(breakpad)
if(NOT breakpad_POPULATED)
    FetchContent_Populate(breakpad)
    add_subdirectory(${breakpad_SOURCE_DIR} ${breakpad_BINARY_DIR})
endif()

# spriterplusplus
FetchContent_Declare(
    spriterplusplus
    GIT_REPOSITORY https://github.com/Squalr/spriterplusplus.git
    GIT_TAG 19a1e397e4de8597955d0cc9387a53b2a36a2625
)
FetchContent_GetProperties(spriterplusplus)
if(NOT spriterplusplus_POPULATED)
    FetchContent_Populate(spriterplusplus)
    add_subdirectory(${spriterplusplus_SOURCE_DIR} ${spriterplusplus_BINARY_DIR})
endif()

# spriter2dx
FetchContent_Declare(
    spriter2dx
    GIT_REPOSITORY https://github.com/Squalr/Spriter2dX.git
    GIT_TAG 7aa674bf92a6777a1acb6ded3681424f1227abc9
)
FetchContent_GetProperties(spriter2dx)
if(NOT spriter2dx_POPULATED)
    FetchContent_Populate(spriter2dx)
    strip_cocos_include_prefix("${spriter2dx_SOURCE_DIR}")
    add_subdirectory(${spriter2dx_SOURCE_DIR} ${spriter2dx_BINARY_DIR})
endif()

if(APPLE)
    # AFNetworking is Apple-only; keep target wiring consistent.
    FetchContent_Declare(
        AFNetworking
        GIT_REPOSITORY https://github.com/Squalr/AFNetworking.git
        GIT_TAG 4b65c4bcaee3662e099a49bdfe5dc8e1dbada24f
    )
    FetchContent_GetProperties(AFNetworking)
    if(NOT AFNetworking_POPULATED)
        FetchContent_Populate(AFNetworking)
        add_subdirectory(${afnetworking_SOURCE_DIR} ${afnetworking_BINARY_DIR})
    endif()
endif()
