set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Keep legacy platform flags expected by cocos CMake fragments.
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WINDOWS TRUE)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX TRUE)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(APPLE TRUE)
    set(MACOSX TRUE)
endif()

if(POLICY CMP0072)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()
find_package(OpenGL REQUIRED)

if(APPLE)
    find_package(Iconv REQUIRED)
endif()

# Cocos CMake fragments are written against PROJECT_SOURCE_DIR.
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Core)
