#!/usr/bin/env python3

###################################################################################
# This script will detect unecessary includes in header files.                    #
###################################################################################

import sys
import subprocess

f = open("CheckIncludes.txt", "w")

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
