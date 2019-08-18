Squally
=========
2D Platformer Game for Teaching Game Hacking.

Language: C++

Engine: Cocos-2dx

Platforms: Windows, OSX, and Linux

![Squally Gameplay 1](https://i.imgur.com/M2KMSZ9.png) | ![Squally Gameplay 2](https://i.imgur.com/U3bbo1v.png)
------------ | -------------
![Squally Gameplay 3](https://i.imgur.com/1hvYk3K.png) | ![Squally Gameplay 4](https://i.imgur.com/bOSKa7p.png)
![Squally Gameplay 5](https://i.imgur.com/0WpBLxS.png) | ![Squally Gameplay 6](https://i.imgur.com/iYUfJGq.png)

Contributing
------------
To show support and help us finish development, [get the game on Steam](https://store.steampowered.com/app/770200/Squally/).

For those that wish to help with development, just hop over to the Issues tab and look for things to improve:

Issues |
------------ |
[Easy](https://github.com/Squalr/Squally/labels/good%20first%20issue) |
[Intermediate](https://github.com/Squalr/Squally/labels/good%20first%20issue%20%28intermediate%29) |

To edit maps, download [Tiled](https://www.mapeditor.org/). Maps are kept in Resources/Platformer/Maps/*.tmx.

Compiling Squally
------------
To minimize cross-platform effort, we develop Squally using [VsCode](https://code.visualstudio.com/) with the following extensions:
- C/C++ for Visual Studio Code
- CMake Tools
- (Mac only) CodeLLDB is recommended, as this debugger works better than the default. Just be sure to go into Debug > Breakpoints > Disable C++: on throw

You may also need to install [Ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages) to compile the project.

Squally is comprised of several subrepos, including:
- Cocos2d-x
- Spriter2d-x / SpriterPlusPlus
- Breakpad / AFNetworking
- Vcpkg
- SquallyResources*

Additional dependencies are managed using vcpkg.

**Important:** The Resources/* folder contains all art and sound for Squally, and is a private repository. This is because we do not have exclusive-rights to all of the art in Squally, so we cannot legally publish it. To gain access, purchase the game and submit proof to zacharycanann@gmail.com, and we will grant you access to this repository, under the condition that you do not redistribute the contents of the repository.

To do a fresh build and pull in dependencies:
```
git clone git@github.com:zcanann/Squally.git
cd Squally
git submodule update --init --recursive .
python dep.py init
cd Resources
git lfs pull
```
Due to a timing bug, `python dep.py init` may need to be run twice. Perhaps this is a good first issue for someone :^)

To update dependencies later:
```
git submodule update --init --recursive .
python dep.py update
```
