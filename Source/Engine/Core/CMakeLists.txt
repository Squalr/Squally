#/****************************************************************************
# Copyright (c) 2013 cocos2d-x.org
# Copyright (c) 2014 martell malone
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

# this CMakeLists is to generate Cocos2d-x Engine Library
# build libcocos2d

include(2d/CMakeLists.txt)
include(platform/CMakeLists.txt)
include(math/CMakeLists.txt)
include(renderer/CMakeLists.txt)
include(base/CMakeLists.txt)

include(FetchContent)
include(ExternalProject)

# Statically link all dependencies
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared off" FORCE)
set(BUILD_STATIC_LIBS ON CACHE BOOL "Build static on" FORCE)

add_library(cocos2d STATIC
    cocos2d.h
    cocos2d.cpp
    ${COCOS_2D_HEADER}
    ${COCOS_PLATFORM_HEADER}
    ${COCOS_PHYSICS_HEADER}
    ${COCOS_MATH_HEADER}
    ${COCOS_RENDERER_HEADER}
    ${COCOS_BASE_HEADER}
    ${COCOS_UI_HEADER}
    ${COCOS_EXTENSIONS_HEADER}
    ${COCOS_2D_SRC}
    ${COCOS_PLATFORM_SRC}
    ${COCOS_PHYSICS_SRC}
    ${COCOS_MATH_SRC}
    ${COCOS_RENDERER_SRC}
    ${COCOS_BASE_SRC}
    ${COCOS_UI_SRC}
    ${COCOS_EXTENSIONS_SRC}
)

add_library(cocos2d::cocos2d ALIAS cocos2d)

# Cereal
set(SKIP_PERFORMANCE_COMPARISON ON)
set(BUILD_SANDBOX OFF)
set(BUILD_DOC OFF)
FetchContent_Declare(
    cereal
    GIT_REPOSITORY  https://github.com/USCiLab/cereal.git
    GIT_TAG         v1.3.2
)
FetchContent_GetProperties(cereal)
if(NOT cereal_POPULATED)
    FetchContent_Populate(cereal)
endif()
set(CEREAL_INCLUDE_DIRS ${cereal_SOURCE_DIR}/include)

# tinyxml2
FetchContent_Declare(tinyxml2
    GIT_REPOSITORY https://github.com/leethomason/TinyXML2
    GIT_TAG        9.0.0
)
FetchContent_GetProperties(tinyxml2)
if(NOT tinyxml2_POPULATED)
    FetchContent_Populate(tinyxml2)
    add_subdirectory(${tinyxml2_SOURCE_DIR} ${tinyxml2_BINARY_DIR})
endif()
set(TINYXML2_INCLUDE_DIRS ${tinyxml2_SOURCE_DIR})

# zlib
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    FetchContent_Declare(
        zlib
        GIT_REPOSITORY    https://github.com/madler/zlib.git
        GIT_TAG           v1.2.13
    )
    FetchContent_GetProperties(zlib)
    if(NOT zlib_POPULATED)
        FetchContent_Populate(zlib)
        add_subdirectory(${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
    endif()
    set(ZLIB_INCLUDE_DIRS ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
    set(ZLIB_LIBRARY zlib)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(ZLIB REQUIRED)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_package(ZLIB REQUIRED)
endif()

# libpng
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    FetchContent_Declare(
        libpng
        GIT_REPOSITORY    https://github.com/glennrp/libpng.git
        GIT_TAG           v1.6.40
    )
    FetchContent_GetProperties(libpng)
    if(NOT libpng_POPULATED)
        FetchContent_Populate(libpng)
        set(PNG_SHARED OFF CACHE BOOL "No shared library for libpng" FORCE)
        set(PNG_BUILD_ZLIB ON CACHE BOOL "Force internal zlib for libpng" FORCE)

        set(ZLIB_LIBRARY "${zlib_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}z${CMAKE_STATIC_LIBRARY_SUFFIX}")
        set(ZLIB_INCLUDE_DIR ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})

        add_subdirectory(${libpng_SOURCE_DIR} ${libpng_BINARY_DIR})
    endif()
    set(PNG_INCLUDE_DIRS ${libpng_SOURCE_DIR} ${libpng_BINARY_DIR})
    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        if(CMAKE_BUILD_TYPE MATCHES Debug)
            set(libpng_LIBRARIES ${libpng_BINARY_DIR}/libpng16_staticd.lib)
        else()
            set(libpng_LIBRARIES ${libpng_BINARY_DIR}/libpng16_static.lib)
        endif()
    endif()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_package(PNG REQUIRED)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(PNG REQUIRED)
endif()

# Freetype
FetchContent_Declare(
    Freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG        VER-2-13-0
)
FetchContent_GetProperties(Freetype)
if(NOT Freetype_POPULATED)
    FetchContent_Populate(Freetype)
    set(FT_DISABLE_ZLIB ON CACHE BOOL "Disable zlib for embedded Freetype" FORCE)
    set(FT_DISABLE_BZIP2 ON CACHE BOOL "Disable bzip2 for embedded Freetype" FORCE)
    set(FT_DISABLE_PNG ON CACHE BOOL "Disable libpng for embedded Freetype" FORCE)
    set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "Disable harfbuzz for embedded Freetype" FORCE)
    set(FT_DISABLE_BROTLI ON CACHE BOOL "Disable brotli for embedded Freetype" FORCE)
    add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})
endif()
set(FREETYPE_INCLUDE_DIRS "${freetype_BINARY_DIR}/include;${freetype_SOURCE_DIR}/include")
set(FREETYPE_LIBRARIES freetype)

# GLEW
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(GLEW_INCLUDE_DIRS "/usr/local/opt/glew/include/GL")
    set(GLEW_LIBRARIES "/usr/local/opt/glew/lib/libGLEW.dylib")

    message(STATUS "GLEW_LIBRARIES = ${GLEW_LIBRARIES}")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(GLEW REQUIRED)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    FetchContent_Declare(
        GLEW
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake
        GIT_TAG glew-cmake-2.2.0
    )
    FetchContent_MakeAvailable(GLEW)
endif()

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3.8
)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) # don't build docs
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE) # don't build tests
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build examples
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

# C++20
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_compile_features(cocos2d PUBLIC cxx_std_20 c_std_99)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_compile_features(cocos2d PUBLIC cxx_std_20 c_std_99)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_compile_features(cocos2d PUBLIC cxx_std_17 c_std_99)
endif()

# PIC, Unity Build
set_target_properties(cocos2d PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    # UNITY_BUILD ON # Causes build issues on OSX
    UNITY_BUILD_BATCH_SIZE 64
)

# target_precompile_headers(cocos2d PUBLIC
    # "$<$<COMPILE_LANGUAGE:CXX>:precheader.h>"
# )

# Include Interface
target_include_directories(cocos2d
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/Core
        ${PROJECT_SOURCE_DIR}/extensions
        ${CMAKE_CURRENT_LIST_DIR}
        ${CEREAL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIRS}
        ${PNG_INCLUDE_DIRS}
        ${TINYXML2_INCLUDE_DIRS}
        ${FREETYPE_INCLUDE_DIRS}
    PRIVATE
        ${COCOS_PLATFORM_INCLUDE_PATHS}
)

# Dependencies
target_link_libraries(cocos2d
    PUBLIC
        glfw
        $<$<PLATFORM_ID:Windows>:zlib>

        $<$<PLATFORM_ID:Linux>:${GLEW_LIBRARIES}>
        $<$<PLATFORM_ID:Darwin>:${GLEW_LIBRARIES}>
        $<$<PLATFORM_ID:Windows>:libglew_static>

    PRIVATE
        # dependencies
        OpenGL::GL
        tinyxml2
        ${FREETYPE_LIBRARIES}        

        $<$<PLATFORM_ID:Windows>:${libpng_LIBRARIES}>
        $<$<PLATFORM_ID:Darwin>:PNG::PNG>
        $<$<PLATFORM_ID:Linux>:PNG::PNG>

        # required platform dependencies
        $<$<PLATFORM_ID:Darwin>:Iconv::Iconv>
        $<$<PLATFORM_ID:Windows>:ws2_32>
        $<$<PLATFORM_ID:Windows>:winmm>
        $<$<PLATFORM_ID:Windows>:version>
)

# Definitions
target_compile_definitions(cocos2d
    PRIVATE
        $<$<PLATFORM_ID:Windows>:_CRT_SECURE_NO_WARNINGS>fontco
        $<$<PLATFORM_ID:Windows>:_SCL_SECURE_NO_WARNINGS>

    PUBLIC
        $<$<CONFIG:Debug>:COCOS2D_DEBUG>

        $<$<PLATFORM_ID:Windows>:UNICODE>
        $<$<PLATFORM_ID:Windows>:_UNICODE>
        $<$<PLATFORM_ID:Windows>:WIN32>
        $<$<PLATFORM_ID:Windows>:_WIN32>
        $<$<PLATFORM_ID:Windows>:CC_STATIC>
        $<$<PLATFORM_ID:Windows>:COCOS2DXWIN32_EXPORTS>
        $<$<PLATFORM_ID:Darwin>:USE_FILE32API>
        $<$<PLATFORM_ID:Darwin>:TARGET_OS_MAC>
        $<$<PLATFORM_ID:Linux>:LINUX>
)

# Private Compile Options
target_compile_options(cocos2d PRIVATE
    # Enable all warnings on non-windows platforms
    $<$<NOT:$<PLATFORM_ID:Windows>>:-Wall>

    # Disable specific warnings (TODO: why?)
    $<$<PLATFORM_ID:Windows>:-wd4005>
    $<$<PLATFORM_ID:Windows>:-wd4056>
    $<$<PLATFORM_ID:Windows>:-wd4099>
    $<$<PLATFORM_ID:Windows>:-wd4244>
    $<$<PLATFORM_ID:Windows>:-wd4251>
    $<$<PLATFORM_ID:Windows>:-wd4334>
    $<$<PLATFORM_ID:Windows>:-wd4514>
    $<$<PLATFORM_ID:Windows>:-wd4710>
    $<$<PLATFORM_ID:Windows>:-wd4820>
    $<$<PLATFORM_ID:Windows>:-wd4996>

    $<$<NOT:$<PLATFORM_ID:Windows>>:-Wno-deprecated-declarations>
    $<$<NOT:$<PLATFORM_ID:Windows>>:$<$<COMPILE_LANGUAGE:CXX>:-Wno-invalid-offsetof>>
    $<$<NOT:$<PLATFORM_ID:Windows>>:$<$<COMPILE_LANGUAGE:CXX>:-Wno-reorder>>
)
