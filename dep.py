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
    parser.add_argument("-t", "--triplet", help="vcpkg triplet (use vcpkg default is not specified")

    args = parser.parse_args()

    if args.triplet is None:
        args.triplet=""

    func = FUNCTION_MAP[args.command[0]]
    if args.command[0] == "install":
        install(args.command[1], args.common, args.triplet)
    else:
        if (len(args.command) > 1):
            func(args.command[1], args.triplet)
        else:
            func(args.triplet)

    return 0

def bootstrap(triplet):
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

def init(triplet):
    bootstrap(triplet)
    update(triplet)

def update(triplet):
    with open('requirements.json', 'r+') as fp:
        manifest = json.load(fp)

        # install common deps
        for line in manifest["common"]:
            print ("installing: " + line)
            install(line.strip(), True, triplet)
            
        # install platform deps
        if _platform == "linux" or _platform == "linux2":
            requirements = manifest["linux"]
        elif _platform == "darwin":
            requirements = manifest["darwin"]
        elif _platform == "win32" or _platform == "win64":
            requirements = manifest["windows"]

        for line in requirements:
            print ("installing: " + line)
            install(line.strip(), False, triplet)

def search(searchString, triplet):
    print(shell_exec(["./vcpkg/vcpkg", "search" , searchString]).decode('utf-8'))

def install(packageString, common, triplet):
    s = packageString;
    if len(triplet) > 0:
        s += ":" + triplet

    p = Popen(["./vcpkg/vcpkg", "install" , s], bufsize=1)
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
