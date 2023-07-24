# Copyright 2023 Squalr. Inc.

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

# Fetches and compiles SFML from source in a cross-platform way. Technology is great sometimes.
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

# SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.0
)
FetchContent_GetProperties(SFML)
if(NOT SFML_POPULATED)
    FetchContent_Populate(SFML)
    set(SFML_BUILD_AUDIO ON)
    set(SFML_BUILD_GRAPHICS OFF)
    set(SFML_BUILD_WINDOW OFF)
    set(SFML_BUILD_NETWORK OFF)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


# target_precompile_headers(${PROJECT_NAME} PUBLIC
  # "$<$<COMPILE_LANGUAGE:CXX>:precheader_squally.h>"
# )

# C++20
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_compile_features(cocos2d PUBLIC cxx_std_20 c_std_99)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_compile_features(cocos2d PUBLIC cxx_std_20 c_std_99)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_compile_features(cocos2d PUBLIC cxx_std_17 c_std_99)
endif()

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
    ${SFML_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${OPENGL_gl_LIBRARY}
    
    # sfml-graphics
    sfml-audio
    # sfml-window
    # sfml-system

    # internal dependencies
    cocos2d::cocos2d
    spriter2dx::spriter2dx
    SteamWorks::API
    breakpad::client
    
    # sfml-graphics
    # sfml-audio
    # sfml-window
    # sfml-system

    # platform dependencies
    $<$<PLATFORM_ID:Windows>:iphlpapi>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<PLATFORM_ID:Windows>:UNICODE>
    $<$<PLATFORM_ID:Windows>:_UNICODE>
    SFML_STATIC
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

# Windows DLLs
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        add_custom_command(TARGET Squally POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/build/_deps/zlib-build/zlibd.dll"
            "${PROJECT_SOURCE_DIR}/build/bin/")
    else()
        add_custom_command(TARGET Squally POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/build/_deps/zlib-build/zlib.dll"
            "${PROJECT_SOURCE_DIR}/build/bin/")
    endif()
    add_custom_command(TARGET Squally POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/build/_deps/sfml-src/extlibs/bin/x86/openal32.dll"
        "${PROJECT_SOURCE_DIR}/build/bin/")
endif()

# Copy game resources. On windows this is stupidly slow, so please manually call CopyResources.py instead.
# I guess this also became slow on OSX, just commenting this out.
# if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_directory
#             "${PROJECT_SOURCE_DIR}/Resources"
#             $<$<PLATFORM_ID:Linux>:$<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources>
#             $<$<PLATFORM_ID:Darwin>:$<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources>
#             $<$<PLATFORM_ID:Windows>:$<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources>
#     )
# endif()
