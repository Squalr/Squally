cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Find platform specific dependencies
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(PkgConfig)
    pkg_check_modules(GTKMM gtkmm-3.0)
    set(LAUNCHER_ADDITIONAL_LIBS
        ${GTKMM_LIBRARIES}
        pthread
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_library(COCOA_LIBRARY Cocoa)
    set(LAUNCHER_ADDITIONAL_LIBS
        ${COCOA_LIBRARY}
        AFNetworking
    )
endif()

# Launcher executable
add_executable(Launcher
    # Hack until we fix the breakpad utf library vs the cocos one
    ${PROJECT_SOURCE_DIR}/external/breakpad/src/common/convert_UTF.c

    # Platform Specific Sources
    $<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/proj.linux/Launcher.cpp>
    $<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/proj.mac/Launcher/LauncherAppDelegate.mm>
    $<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/proj.mac/Launcher/main.mm>
    $<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/proj.win32/Launcher.cpp>
    $<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/proj.win32/game.rc>
)

# Force C++11
target_compile_features(Launcher PRIVATE cxx_std_11 c_std_99)

# Compile options
target_compile_options(Launcher PRIVATE
    $<$<PLATFORM_ID:Darwin>:-fobjc-arc>
)

# Make sure the launcher is in the same directory as the Squally binary
set_target_properties(Launcher PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Platform Specific Properties
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set_target_properties(Launcher PROPERTIES WIN32_EXECUTABLE ON)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # set rpath on linux so launcher can search for gtk relative to itself
    set_target_properties(Launcher PROPERTIES LINK_FLAGS "-Wl,-rpath,'$ORIGIN/lib'")
endif()

# Include directories
target_include_directories(Launcher PRIVATE
    ${PROJECT_BINARY_DIR}/Generated
    ${GTKMM_INCLUDE_DIRS}
)

# Dependencies
target_link_libraries(Launcher PRIVATE
    breakpad::client
    ${LAUNCHER_ADDITIONAL_LIBS}
)
