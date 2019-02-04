#!/usr/bin/python2
###################################################################################
# This script will bootstrap vspkg and grab any neccessary dependencies           #
# Run this script every time you pull                                             #
###################################################################################

import argparse
import sys
import subprocess
import json
import os
from sys import platform as _platform
from subprocess import check_output as shell_exec, Popen

def main():
    # Setup environment
    os.environ['MACOSX_DEPLOYMENT_TARGET'] = '10.10'

    # Run commands
    FUNCTION_MAP = {
        'init' : init,
        'install' : install,
        'search' : search,
        'update' : update,
    }

    parser = argparse.ArgumentParser()
    parser.add_argument('command', nargs='+')
    parser.add_argument("-c", "--common", help="operation operates on the common set", action="store_true")

    args = parser.parse_args()

    func = FUNCTION_MAP[args.command[0]]
    if args.command[0] == "install":
        install(args.command[1], args.common)
    else:
        if (len(args.command) > 1):
            func(args.command[1])
        else:
            func()

    return 0

def bootstrap():
    p = ""
    # linux
    if _platform == "linux" or _platform == "linux2":
        p = Popen(["./vcpkg/bootstrap-vcpkg.sh"], bufsize=1)

    # MAC OS X
    elif _platform == "darwin":
        p = Popen(["./vcpkg/bootstrap-vcpkg.sh"], bufsize=1)

    # Windows
    elif _platform == "win32":
        p = Popen(["./vcpkg/bootstrap-vcpkg.bat"], bufsize=1)

    # Windows 64-bit 
    elif _platform == "win64":
        p = Popen(["./vcpkg/bootstrap-vcpkg.bat"], bufsize=1)
    p.wait()

def init():
    bootstrap()
    update()

def update():
    with open('requirements.json', 'r+') as fp:
        manifest = json.load(fp)
        requirements = manifest["common"]
        if _platform == "linux" or _platform == "linux2":
            requirements.extend(manifest["linux"])
        elif _platform == "darwin":
            requirements.extend(manifest["darwin"])
        elif _platform == "win32" or _platform == "win64":
            requirements.extend(manifest["windows"])

        for line in requirements:
            print ("installing: " + line)
            install(line.strip())

def search(searchString):
    print(shell_exec(["./vcpkg/vcpkg", "search" , searchString]).decode('utf-8'))

def install(packageString, common=False):
    p = Popen(["./vcpkg/vcpkg", "install" , packageString], bufsize=1)
    p.wait()
    if p.returncode != 0:
        return

    # Select a set to write the dependency to
    if common:
        selectedSet = "common"
    elif _platform == "win32" or _platform == "win64":
        selectedSet = "windows"
    elif _platform == "linux" or _platform == "linux2":
        selectedSet = "linux"
    elif _platform == "darwin":
        selectedSet = "darwin"
        
    # Write the dependency into our requirements file
    with open("requirements.json", "r+") as fp:
        manifest = json.load(fp)
        if (packageString not in manifest[selectedSet]) and (packageString not in manifest["common"]):
            manifest[selectedSet].append(packageString)

        with open("requirements.json", "w") as wp:
            json.dump(manifest, wp, indent=4, sort_keys=True)

if __name__ == '__main__':
    main()
