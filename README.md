Squally
=========
2D Platformer Game for Teaching Game Hacking - C++/cocos2d-x

Checking out
------------
```
git clone --recurse-submodules git@github.com:zcanann/Squally.git
cd Squally

# to update later
git submodule update --init --recursive .
```

Dependencies
---------
Dependencies are managed via vcpkg which is conviently bundled into this repo
- To get this setup cd into the vcpkg directory and run either bootstrap-vcpkg.bat or bootstrap-vcpkg.sh depending on your platform
- CMake Tools

Compiling
---------
To minimize cross-platform effort, we're using VsCode with the following extensions:
- C/C++ for Visual Studio Code
- CMake Tools