Squally
=========
2D Platformer Game for Teaching Game Hacking - C++/cocos2d-x

Checking out
------------
```
git clone git@github.com:zcanann/Squally.git
cd Squally

# checkout submodules (cocos is not recursive because it had other submodules WE DONT want)
git submodule update --init --recursive external/breakpad
git submodule update --init cocos2d
cd cocos2d
git submodule update --init external
cd ..
```

Compiling
---------
To minimize cross-platform effort, we're using VsCode with the following extensions:
- C/C++ for Visual Studio Code
- CMake Tools
