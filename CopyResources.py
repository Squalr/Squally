#!/usr/bin/env python3

###################################################################################
# This script will generate the target files inside CMakeLists.txt                #
# Run this script every time files are added to the Squally/Source/ directory.    #
###################################################################################

from dirsync import sync
from os import listdir
from os import path
from os.path import isfile, join, splitext, abspath, relpath, realpath, basename, relpath
import os
from sys import platform as _platform

def main():
    if _platform == "win32" or _platform == "win64":
        copyResources()
    else:
        print("This script is currently Windows only.");

def copyResources():
    projectRoot = abspath(join(realpath(__file__), ".."))
    sourcePathPublic = join(projectRoot, "Resources/Public/")
    sourcePathPrivate = join(projectRoot, "Resources/Private/")

    binRoot = abspath(join(realpath(__file__), "../build/bin/"))
    destPathPublic = join(binRoot, "Resources/Public/")
    destPathPrivate = join(binRoot, "Resources/Private/")
    
    doSync(sourcePathPublic, destPathPublic);
    doSync(sourcePathPrivate, sourcePathPrivate);

def doSync(source, dest):
    print("SYNCING: " + source + " => " + dest)
    sync(source, dest, 'sync', content=True)
    

if __name__ == '__main__':
    main()
