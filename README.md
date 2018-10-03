Squally
=========
2D Platformer Game for Teaching Game Hacking - C++/cocos2d-x

Checking out
------------
```
# I'm explicitly not using recursive clone since cocos2d has some submodules we'd like to leave out for the moment
git clone git@github.com:zcanann/Squally.git
cd Squally

# Checkout cocos2d submodule and external submodule
git submodule update --init cocos2d
cd cocos2d
git submodule update --init cocos2d/external
cd ..
```

Compiling
---------
To minimize cross-platform effort, we're using VsCode with the following extensions:
- C/C++ for Visual Studio Code
- CMake Tools
