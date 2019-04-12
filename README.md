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
python dep.py update
```

Publishing to Itch and Steam
---------

The gDrive SquallyDeploy folder is used as a repository for deploy files. Git is not effective here, as the binaries are large and change often. Simply run the `deploy.py` script. Currently, we release symbol files because it doesn't really matter.

Note: Itch.io builds and Steam builds are identical. The difference is the files shipped:

Cases:
- Steam		Steam DLLs are present, `steam_appid.txt` is NOT present.
- Debug		Both files are present, and Steam debug mode is used.
- Itch		Neither file is present.


Dependencies
---------
Dependencies are managed via vcpkg which is conviently bundled into this repo
- I wrote dep.py as a wrapper to vcpkg, use python dep.py search <packagename> or python dep.py install <packagename>
- Newly installed dependencies will automatically be added to requirements.txt which should be committed along with your changes, this is how others will install your new dependency via dep.py update
- Once installed, you'll need to include the headers in our cmake file and link the library to the squally binary
    - For some modules, youll recieve commands you can add to CMakeLists.template directly, just replace "main" with ${AppName}
    - For others you'll have to manually wire things up, see asmjit as an example. More details here: https://github.com/Microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md#handling-libraries-without-native-cmake-support

On intial clone use dep.py to initalize dependencies
`python dep.py init`

when updating later run
`python dep.py update`

---------
To minimize cross-platform effort, we're using VsCode with the following extensions:
- C/C++ for Visual Studio Code
- CMake Tools