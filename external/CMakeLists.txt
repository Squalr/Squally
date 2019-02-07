cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/breakpad)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/spriterplusplus)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/spriter2dx)

if(APPLE)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/AFNetworking)
endif()
