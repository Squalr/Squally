cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Add externals
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/asmjit)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/breakpad)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/steam)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Udis86)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Fasm)

if(APPLE)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/AFNetworking)
endif()