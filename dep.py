#!/usr/bin/env python3

###################################################################################
# This script will bootstrap vspkg and grab any neccessary dependencies           #
# Run this script every time you pull                                             #
###################################################################################

import argparse
import sys
import subprocess
import json
import os
import time
from sys import platform as _platform
from subprocess import check_output as shell_exec, Popen

def main():
    # Setup environment
    os.environ['MACOSX_DEPLOYMENT_TARGET'] = '10.10'

    # Parse args
    parser = argparse.ArgumentParser()
    parser.add_argument('command', nargs='+', help="accepted commands: init, update, search, install")
    parser.add_argument("-c", "--common", help="operation operates on the common set", action="store_true")
    parser.add_argument("-t", "--triplet", help="vcpkg triplet (use vcpkg default is not specified", default="")
    
    try:
    	args = parser.parse_args()
    except:
        parser.print_help()
        return 0
        
    if len(args.command) <= 0:
        parser.print_help()
        return 0

    # Command
    if args.command[0] == "init":
        init(args.triplet)
    
    elif args.command[0] == "install":
        if len(args.command) <= 1:
            print("please specify a package to install")
            parser.print_help()
            return 0
        install(args.command[1], args.common, args.triplet)

    elif args.command[0] == "search":
        search(args.command[1])

    elif args.command[0] == "update":
        update(args.triplet)
    
    else:
        parser.print_help()

    return 0

def integrate():
    if _platform == "linux" or _platform == "linux2":
        p = Popen(["./vcpkg/vcpkg", "integrate", "install"])
    elif _platform == "darwin":
        p = Popen(["./vcpkg/vcpkg", "integrate", "install"])
    elif _platform == "win32":
        p = Popen([".\\vcpkg\\vcpkg", "integrate", "install"])

def bootstrap():
    if _platform == "linux" or _platform == "linux2":
        p = Popen(["./vcpkg/bootstrap-vcpkg.sh"], bufsize=1)
    elif _platform == "darwin":
        p = Popen(["./vcpkg/bootstrap-vcpkg.sh"], bufsize=1)
    elif _platform == "win32":
        p = Popen(".\\vcpkg\\bootstrap-vcpkg.bat", shell=True, bufsize=1)

def init(triplet=""):
    bootstrap()
    update(triplet)
    integrate()

def update(triplet=""):
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
        elif _platform == "win32":
            requirements = manifest["windows"]

        for line in requirements:
            print ("installing: " + line)
            install(line.strip(), False, triplet)
    integrate()

def search(searchString):
    print(shell_exec(["./vcpkg/vcpkg", "search" , searchString]).decode('utf-8'))

def install(packageString, common=True, triplet=""):
    s = packageString
    if len(triplet) > 0:
        s += ":" + triplet

    # We ignore the error stream as vcpkg reports error on stdout and all we get is a spam of
    # complaints about some vcpkg lock file not being present (this happens when vcpkg is run
    # quickly).
    if _platform == "linux" or _platform == "linux2":
        p = Popen(["./vcpkg/vcpkg", "install" , s], stderr=subprocess.DEVNULL)
    else:
        p = Popen(["./vcpkg/vcpkg", "install" , s])

    p.wait()
    if p.returncode != 0:
        print()
        print("dep.py: A problem appears to have occurred, writing package to requirements.json skipped.")
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
