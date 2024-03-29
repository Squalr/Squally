# Copyright 2023 Squalr. Inc.

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Squally VERSION 1.2.2 LANGUAGES C CXX)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SteamWorks REQUIRED)

###############################################################################
###############################################################################

# Fix tinyxml2 relwithdebinfo configuration (chooses debug instead of release for relwithdebinfo)
# set_target_properties(tinyxml2::tinyxml2 PROPERTIES
#     MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE
# )

# Bundled Dependencies
add_subdirectory(${PROJECT_SOURCE_DIR}/cocos2d)
add_subdirectory(${PROJECT_SOURCE_DIR}/external)

# Capture configuration to header
configure_file(
    ${PROJECT_SOURCE_DIR}/Source/Config.h.in 
    ${CMAKE_BINARY_DIR}/Generated/Config.h
)

# Sources
add_subdirectory(${PROJECT_SOURCE_DIR}/Source)
# add_subdirectory(${PROJECT_SOURCE_DIR}/Launcher)
