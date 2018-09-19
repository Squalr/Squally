###################################################################################
# This script will generate the CMakeLists.txt target files.                      #
# Run this script every time files are added to the Squally/Source/ directory.    #
###################################################################################

from os import listdir
from os import path
from os.path import isfile, join, splitext, abspath, relpath, realpath, basename, relpath
import os

inputTemplate = "CMakeLists.template"
outputFile = "CMakeLists.txt"

currentPath = realpath(__file__);
sourcePath = abspath(join(join(currentPath, ".."), "Source"))
cppFiles = []
hFiles = []

for root, dirnames, filenames in os.walk(sourcePath):
	for filename in filenames:
		pathStr = join(relpath(root, currentPath), filename).replace("\\", "/").lstrip(".").lstrip("/");
		
		print(pathStr)
		if filename.lower().endswith("cpp"):
			cppFiles.append(pathStr)
			continue
		if filename.lower().endswith("h"):
			hFiles.append(pathStr)
			continue
				
template = open(inputTemplate, 'r').read()

with open(outputFile, 'w') as cmakeFile:
	cppList = "\n\t".join(cppFiles);
	hList = "\n\t".join(hFiles);
	
	template = template.replace("{{ CMAKE_GENRATE_CPP }}", cppList)
	template = template.replace("{{ CMAKE_GENRATE_H }}", hList)
	
	cmakeFile.write(template)
