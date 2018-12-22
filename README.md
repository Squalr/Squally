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
- Then from the main squally directory you can run ./vcpkg/vcpkg search <packagename> or ./vcpkg/vcpkg install <packagename> 
- Once installed, you'll need to include the headers in our cmake file and link the library to the squally binary
    - For some modules, youll recieve commands you can add to CMakeLists.template directly, just replace "main" with ${AppName}
    - For others you'll have to manually wire things up, see asmjit as an example. More details here: https://github.com/Microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md#handling-libraries-without-native-cmake-support

On intial clone use vcpkg to install the following dependencies
- asmjit


Compiling
---------
To minimize cross-platform effort, we're using VsCode with the following extensions:
- C/C++ for Visual Studio Code
- CMake Tools