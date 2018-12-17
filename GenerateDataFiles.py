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

def main():
	entityDataPath = abspath(join(join(realpath(__file__), ".."), "Data/Entities.json"))
	
	with open(entityDataPath, 'r') as dataFile:
		entityDictionary = json.load(dataFile)
		
	for entityData in entityDictionary:
		print(entityDictionary[entityData])
		#parseEntity(entityData)
	

def parseEntity(entityName, entityData):
	# Load data
	entityPath = entityData['Path']
	entityScale = entityData['Scale']
	entitySize = entityData['Size']
	entityOffset = entityData['Offset']
	
	# Construct variables from parsed data
	pathRoot = "Source/Entities/Platformer/" + entityPath + "/"
	animationFile = "Resources/Platformer/Entities/" + entityPath + "/" + "entityName"
	outputHeader = entityName + ".h"
	outputClass = entityName + ".cpp"
			
	with open(pathRoot + outputHeader,'w+') as h, open(pathRoot + outputClass,'w+') as cpp:

		warning = ( "///////////////////////////////////////////////////////////////////////////////////////////" + "\n" +
			"// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //" + "\n" +
			"///////////////////////////////////////////////////////////////////////////////////////////" + "\n")

		h.write(warning)
		h.write("#pragma once" + "\n");
		h.write("#include <string>" + "\n");
		h.write("\n");
		h.write("class " + entityName + "\n");
		h.write("{" + "\n");
		h.write("public:" + "\n");

		cpp.write(warning);
		cpp.write("\n");
		cpp.write("#include \"" + outputHeader + "\"" + "\n");
		cpp.write("#include <string>" + "\n");
		cpp.write("\n");

		h.write("};" + "\n")

if __name__ == '__main__':
    main()