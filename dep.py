###################################################################################
# This script will bootstrap vspkg and grab any neccessary dependencies           #
# Run this script every time you pull                                             #
###################################################################################

import argparse
import sys
import subprocess
from sys import platform as _platform
from subprocess import check_output as shell_exec, Popen

def main():

    FUNCTION_MAP = {
        'init' : init,
        'install' : install,
        'search' : search,
        'update' : update,
    }

    parser = argparse.ArgumentParser()
    parser.add_argument('command', nargs='+')

    args = parser.parse_args()

    func = FUNCTION_MAP[args.command[0]]
    if (len(args.command) > 1):
        func(args.command[1])
    else:
        func()

    return 0

def bootstrap():
    p = ""
    # linux
    if _platform == "linux" or _platform == "linux2":
        p = Popen(["./vcpkg/bootstrap-vcpkg.sh"], stdout=subprocess.PIPE, bufsize=1)

    # MAC OS X
    elif _platform == "darwin":
        p = Popen(["./vcpkg/bootstrap-vcpkg.sh"], stdout=subprocess.PIPE, bufsize=1)

    # Windows
    elif _platform == "win32":
        p = Popen(["./vcpkg/bootstrap-vcpkg.bat"], stdout=subprocess.PIPE, bufsize=1)

    # Windows 64-bit 
    elif _platform == "win64":
        p = Popen(["./vcpkg/bootstrap-vcpkg.bat"], stdout=subprocess.PIPE, bufsize=1)

    for outputLine in iter(p.stdout.readline, b''):
        print(outputLine.decode('utf-8'))
    
    p.stdout.close()
    p.wait()
    
def init():
    bootstrap()
    update()

def update():
    with open('requirements.txt') as fp:
        for line in fp:
            print ("installing: " + line)
            install(line.strip())

def search(searchString):
    print(shell_exec(["./vcpkg/vcpkg", "search" , searchString]).decode('utf-8'))

def install(packageString):
    try:
        p = Popen(["./vcpkg/vcpkg", "install" , packageString], stdout=subprocess.PIPE, bufsize=1)
        for outputLine in iter(p.stdout.readline, b''):
            print(outputLine.decode('utf-8'))
    
        p.stdout.close()
        p.wait()

        # Write the dependency into our requirements file
        with open("requirements.txt", "r+") as file:
            for line in file:
                if line.strip() == packageString:
                    break
            else: # not found, we are at the eof
                file.write('\n' + packageString) # append missing data
    except:
        print("Failed to Install Package: " + packageString + " An error occurred, make sure you spelled the package name right")


if __name__ == '__main__':
    main()