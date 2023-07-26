Squally
=========
2D Platformer Game for Teaching Game Hacking.

Language: C++

Engine: Cocos-2dx

Platforms: Windows, OSX, and Linux

[Steam Page](https://store.steampowered.com/app/770200/Squally/) / Discord: https://discord.gg/3maVXN5

![Squally Gameplay 1](https://i.imgur.com/M2KMSZ9.png) | ![Squally Gameplay 2](https://i.imgur.com/8jsCkX2.png)
------------ | -------------
![Squally Gameplay 3](https://i.imgur.com/1hvYk3K.png) | ![Squally Gameplay 4](https://i.imgur.com/bOSKa7p.png)
![Squally Gameplay 5](https://i.imgur.com/D9aIKSJ.png) | ![Squally Gameplay 6](https://i.imgur.com/iYUfJGq.png)
![Squally Gameplay 7](https://i.imgur.com/wGVSBFR.png) | ![Squally Gameplay 8](https://i.imgur.com/U7C2fXh.png)

Contributing
------------
To show support and help us finish development, [get the game on Steam](https://store.steampowered.com/app/770200/Squally/).

For those that wish to help with development, just hop over to the Issues tab and look for things to improve:

Issues |
------------ |
[Easy](https://github.com/Squalr/Squally/labels/good%20first%20issue) |
[Intermediate](https://github.com/Squalr/Squally/labels/good%20first%20issue%20%28intermediate%29) |

To edit maps, download [Tiled](https://www.mapeditor.org/). Maps are kept in Resources/Public/Platformer/Maps/*.tmx.

Compiling Squally
------------
To minimize cross-platform effort, we develop Squally using [VsCode](https://code.visualstudio.com/) with the following extensions:
- C/C++ for Visual Studio Code
- CMake Tools
- (Mac only) CodeLLDB is recommended, as this debugger works better than the default. Just be sure to go into Debug > Breakpoints > Disable C++: on throw

You will also need the following software to compile the project:
- Cmake (The CMake Tools extension does not include the cmake binaries)
    - Windows: Download the [installer](https://cmake.org/download/)
    - OSX: Use [Brew](https://brew.sh/) to install Cmake with the command `brew install cmake`
    - Linux: Install via the instructions [here](https://cgold.readthedocs.io/en/latest/first-step/installation.html)
- [Ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages)
- Python 2.7.x or 3.x -- all scripts should be compatible with either version.

- Mac Software:
    - brew install cmake
    - brew install ninja
    - brew install freeglut

Squally is comprised of several subrepos, including:
- Cocos2d-x
- Spriter2d-x / SpriterPlusPlus
- Breakpad / AFNetworking
- SquallyResources* (Not public, copy this from Steam library)

**Linux Release**
These steps are only for compiling Squally specifically for RELEASING to Steam. Linux is agonizing torture, but the steps are as follows:

install podman (apt-get or whatever)
run `podman pull registry.gitlab.steamos.cloud/steamrt/sniper/sdk`
cd into `Squally`
modify `./proj.linux/LoadSteamRuntime.sh` to point to your Squally directory. Then pick which directory to mount it to in the Steam Runtime.
Run `./proj.linux/LoadSteamRuntime.sh`
cd into the mounted Squally directory
run `mkdir build`
run `cd build`
run `cmake ..`
run `cd ..`
run `cmake --build ./build`

**Important:** We do not have the legal rights to distribute the art/sound in Squally. To get a copy of the `Squally/Resources/Private` folder, copy it from a purchased copy of the game. See the section below for details.

To do a fresh build and pull in dependencies:
```
git clone git@github.com:Squalr/Squally.git
cd Squally
git submodule update --init --recursive .
```

From here, simply open the Squally/ folder in VsCode and compile using one of the following:
- OSX: Clang 7.0.x
- Windows: MSVC (VS2019 x86)
- Linux: GCC

To update dependencies later:
```
git submodule update --init --recursive .
```

Getting the Resource Folder
------------
We could not include the `Squally/Resources/Private` folder in this repository, because a lot of the art in this game comes from asset stores. This means we have non-exclusive rights to the art, and cannot redistribute it for free. This means the Resources must be copied from a legally purchased copy of the game.

The `Squally/Resources/Private` folder in the Steam copy of Squally will correspond to the master branch of this repository.

![Squally resource folder](https://i.imgur.com/5PaDZiG.png)

Additional learning resources
------------
Learning game hacking? Check out content from our partner [Guided Hacking](https://guidedhacking.com/)
