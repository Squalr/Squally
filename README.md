Squally
=========
2D Platformer Game for Teaching Game Hacking. Written in C++/cocos2d-x, runs on Windows, OSX, and Linux.

![Squally Gameplay 1](https://i.imgur.com/M2KMSZ9.png) | ![Squally Gameplay 2](https://i.imgur.com/U3bbo1v.png)
------------ | -------------
![Squally Gameplay 3](https://i.imgur.com/1hvYk3K.png) | ![Squally Gameplay 4](https://i.imgur.com/bOSKa7p.png)
![Squally Gameplay 5](https://i.imgur.com/0WpBLxS.png) | ![Squally Gameplay 6](https://i.imgur.com/iYUfJGq.png)


Compiling Squally
------------
To minimize cross-platform effort, we develop Squally using [VsCode](https://code.visualstudio.com/) with the following extensions:
- C/C++ for Visual Studio Code
- CMake Tools

Squally is comprised of several subrepos, including:
- Cocos2d-x
- Spriter2d-x / SpriterPlusPlus
- Breakpad / AFNetworking
- Vcpkg

Additional dependencies are managed using vcpkg.

**Important:** The Resources/* folder contains all art and sound for Squally, and is a private repository. This is because we do not have exclusive-rights to all of the art in Squally, so we cannot legally publish it. To gain access, purchase the game and submit proof to zacharycanann@gmail.com, and we will grant you access to this repository, under the condition that you do not redistribute the contents of the repository.

To do a fresh build and pull in dependencies:
```
git clone --recurse-submodules git@github.com:zcanann/Squally.git
cd Squally
python dep.py init
```


To update dependencies later:
```
git submodule update --init --recursive .
python dep.py update
```
