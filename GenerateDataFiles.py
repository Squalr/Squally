#!/usr/bin/env python3

####################################################################################
# This script will generate all cpp/h files from data in the Data directory.       #
# Run this script every time data files are updated in the Squally/Data directory. #
###################################################################################$

from os import listdir
from os import path
from os.path import isfile, join, splitext, abspath, realpath, basename, relpath
import json
import os
import re
import sys

import importlib.util

def main():
	continueStr = "n"

	print("This will generate all strings from the project JSON files and will result in a large build time. Continue (y/*)?")

	if (sys.version_info > (3, 0)):
		continueStr = input()
	else:
		continueStr = raw_input()
	
	if (continueStr != "y"):
		print("Script canceled by user")
		return

	print("Generating strings...")

	# Generate string files
	spec = importlib.util.spec_from_file_location("module.name", "Data/Strings/GenerateStringFiles.py")
	entityGenerator = importlib.util.module_from_spec(spec)
	spec.loader.exec_module(entityGenerator)
	entityGenerator.main()
	
if __name__ == '__main__':
    main()
