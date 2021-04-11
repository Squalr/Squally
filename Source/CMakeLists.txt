# Copyright 2019 Squalr
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Squally executable
include(manifest.cmake)
add_executable(${PROJECT_NAME}
    $<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/proj.linux/main.cpp>
    $<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/proj.mac/main.cpp>
    $<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/proj.mac/Icon.icns>
    $<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/proj.win32/main.h>
    $<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/proj.win32/resource.h>
    $<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/proj.win32/main.cpp>
    $<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/proj.win32/game.rc>
    ${GAME_SOURCES}
    ${GAME_HEADERS}
)

# target_precompile_headers(${PROJECT_NAME} PUBLIC
  # "$<$<COMPILE_LANGUAGE:CXX>:precheader_squally.h>"
# )

# C++20
target_compile_features(cocos2d PUBLIC cxx_std_20 c_std_99)

# Target Propeties (PIE and edit the output directory)
set_target_properties(${PROJECT_NAME} PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    UNITY_BUILD ON
    UNITY_BUILD_BATCH_SIZE 64
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/Generated
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    # vcpkg resources
    tinyxml2::tinyxml2

    # internal dependencies
    cocos2d::cocos2d
    spriter2dx::spriter2dx
    SteamWorks::API
    breakpad::client

    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARIES}

    # platform dependencies
    $<$<PLATFORM_ID:Windows>:iphlpapi>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<PLATFORM_ID:Windows>:UNICODE>
    $<$<PLATFORM_ID:Windows>:_UNICODE>
)

# Platform specific target options
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE YES
        MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/proj.mac/Info.plist
    )
    set_source_files_properties(${PROJECT_SOURCE_DIR}/proj.mac/Icon.icns PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources
    )

    # Patch to default segment permissions to allow self-modifying code
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMENT "Patching executable file init_prot to 0x07 (r/w/e for all segments)"
        COMMAND ${PROJECT_SOURCE_DIR}/PostBuildMac.sh
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Supported architecture
    target_compile_options(${PROJECT_NAME} PRIVATE "/arch:SSE2")

    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE YES
    )
    string(REGEX REPLACE "/Z[iI7]" ""
        CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG}"
    )
    string(REGEX REPLACE "/Z[iI7]" ""
        CMAKE_CXX_FLAGS_RELEASE
        "${CMAKE_CXX_FLAGS_RELEASE}"
    )
    string(REGEX REPLACE "/Z[iI7]" ""
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
        "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}"
    )
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Z7")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Z7")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Z7")

    # Allow large multi-class C++ files
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")

    message(${CMAKE_CXX_FLAGS_DEBUG})

    target_link_options(${PROJECT_NAME} PRIVATE
        # Enable to allow profiling on windows:
        # $<$<CONFIG:RELEASE>:/PROFILE>
        # $<$<CONFIG:DEBUG>:/PROFILE>

        # Enable for verbose linker output
        # $<$<CONFIG:DEBUG>:/VERBOSE>
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # setup rpath so binaries can search relative to themselves for libs
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,-rpath,'$ORIGIN/lib'")
endif()

# Install steam appid file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/steam_appid.txt
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Install itch file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/.itch.toml
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Copy steamworks runtime (regex is to switch lib for dll on Windows)
string(REGEX REPLACE "\\.lib$" ".dll" STEAMWORKS_API_LIBRARY_RUNTIME "${STEAMWORKS_API_LIBRARY}")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${STEAMWORKS_API_LIBRARY_RUNTIME}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Copy game resources. On windows this is stupidly slow, so please manually call CopyResources.py instead.
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/Resources"
            $<$<PLATFORM_ID:Linux>:$<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources>
            $<$<PLATFORM_ID:Darwin>:$<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources>
            $<$<PLATFORM_ID:Windows>:$<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources>
    )
endif()
