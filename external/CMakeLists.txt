cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Add externals
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/breakpad)
if(APPLE)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/AFNetworking)
endif()