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

import importlib.util

def main():
	# Generate entities
	spec = importlib.util.spec_from_file_location("module.name", "Data/Entities/GenerateEntityFiles.py")
	entityGenerator = importlib.util.module_from_spec(spec)
	spec.loader.exec_module(entityGenerator)
	entityGenerator.main()
	
	# Generate string files
	spec = importlib.util.spec_from_file_location("module.name", "Data/Strings/GenerateStringFiles.py")
	entityGenerator = importlib.util.module_from_spec(spec)
	spec.loader.exec_module(entityGenerator)
	entityGenerator.main()
	
if __name__ == '__main__':
    main()
