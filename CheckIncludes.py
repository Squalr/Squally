#!/usr/bin/env python3

###################################################################################
# This script will detect unecessary includes in header files.                    #
###################################################################################

import os
import sys
import subprocess

with open("CheckIncludesIntermediate.txt", "w") as f:
    subprocess.call([
        sys.executable,
        'C:/Python38/Scripts/cppclean', #cppclean
        '.',
        '--include-path=Source',
        '--include-path=cocos2d',
        '--include-path=cocos2d/cocos',
        '--include-path=proj.win32',
        '--include-path=proj.linux',
        '--include-path=proj.mac'
    ], stdout=f)
    
ignored_words = ['Squally.dir', 'cocos2d.dir', 'spriter2dx.dir', ' static data ', 'precheader', 'asmjit', 'asmtk', 'libudis86']
    
with open("CheckIncludesIntermediate.txt", "r") as input, open("CheckIncludes.txt", "w") as output:
    for line in input:
        if not any(ignored_word in line for ignored_word in ignored_words):
            output.write(line)

os.remove("CheckIncludesIntermediate.txt")
