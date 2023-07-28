#!/usr/bin/env python3

###################################################################################
# This script will generate the target files inside CMakeLists.txt                #
# Run this script every time files are added to the Squally/Source/ directory.    #
###################################################################################

from dirsync import sync
from os import listdir
from os import path
from os.path import isfile, join, splitext, abspath, relpath, realpath, basename, relpath
import argparse
import os
from sys import platform as _platform

# Initialize the parser
parser = argparse.ArgumentParser(description="Check for --release argument")
parser.add_argument('--release', action='store_true', 
                    help='Include this flag to indicate release')
args = parser.parse_args()

def main():
    print(_platform)
    if _platform == "win32" or _platform == "win64" or _platform == "darwin" or _platform == "linux2":
        copyResources()
    else:
        print("Unsupported platform")

def copyResources():
    projectRoot = abspath(join(realpath(__file__), ".."))
    sourcePathPublic = join(projectRoot, "Resources/Public/")
    sourcePathPrivate = join(projectRoot, "Resources/Private/")

    if _platform == "win32" or _platform == "win64":
        binRoots = [abspath(join(realpath(__file__), "../build/bin/"))]
    elif _platform ==  "darwin":
        binRoots = [abspath(join(realpath(__file__), "../build/bin/Squally.app/Contents/"))]
    elif _platform ==  "linux2":
        binRoots = [abspath(join(realpath(__file__), "../build/bin/"))]
    
    if args.release:
        binRoots = [
            "G://.shortcut-targets-by-id/1ekuO4zIiSeWqZxLnf3Gy7XC3RwPz6UIW/SquallyFiles/SquallyDeploy/content/MacOS/Squally.app/Contents/",
            "G://.shortcut-targets-by-id/1ekuO4zIiSeWqZxLnf3Gy7XC3RwPz6UIW/SquallyFiles/SquallyDeploy/content/Linux/",
            "G://.shortcut-targets-by-id/1ekuO4zIiSeWqZxLnf3Gy7XC3RwPz6UIW/SquallyFiles/SquallyDeploy/content/Windows/",
        ]
    
    for binRoot in binRoots:
        destPathPublic = join(binRoot, "Resources/Public/")
        destPathPrivate = join(binRoot, "Resources/Private/")
        
        doSync(sourcePathPublic, destPathPublic);
        doSync(sourcePathPrivate, destPathPrivate);

def doSync(source, dest):
    print("SYNCING: " + source + " => " + dest)
    sync(source, dest, 'sync', create=True, content=True, ignore=['.git'])
    

if __name__ == '__main__':
    main()
 