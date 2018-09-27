# Install script for directory: F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Squally")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally/proj.win32/engine/external/recast/cmake_install.cmake")
  include("F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally/proj.win32/engine/external/tinyxml2/cmake_install.cmake")
  include("F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally/proj.win32/engine/external/unzip/cmake_install.cmake")
  include("F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally/proj.win32/engine/external/flatbuffers/cmake_install.cmake")
  include("F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally/proj.win32/engine/external/xxhash/cmake_install.cmake")
  include("F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally/proj.win32/engine/external/SpriterPlusPlus/cmake_install.cmake")
  include("F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally/proj.win32/engine/external/asmjit/cmake_install.cmake")
  include("F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally/proj.win32/engine/external/cereal/cmake_install.cmake")
  include("F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally/proj.win32/engine/external/Udis86/cmake_install.cmake")
  include("F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally/proj.win32/engine/external/RapidJson/cmake_install.cmake")
  include("F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally/proj.win32/engine/cocos/core/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "F:/Users/Zachary/Documents/Visual Studio 2017/Projects/Squally/proj.win32/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
