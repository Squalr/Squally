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

Compiling
---------
To minimize cross-platform effort, we're using VsCode with the following extensions:
- C/C++ for Visual Studio Code
- CMake Tools

macOS Release Process
----------------------------
mkdir build-relwithdebinfo
cd build-relwithdebinfo
cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo /path/to/squally
ninja

```
# the following is the manual part with needs to be automated
cd bin/Squally.app/Contents/MacOS
dsymutil Launcher
dsymutil Squally
mv Launcher.dSYM ~/Desktop
mv Squally.dSYM ~/Desktop
strip Launcher
strip Squally
# compress bin/Squally.app (recommend using lzma, it's half the size of zip)
# compress symbols (recommend using lzma, it's a quarter the size of zip)
```
