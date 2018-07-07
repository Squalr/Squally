###################################################################################
# This script will generate the Resources.cpp and Resources.h files.              #
# Run this script every time files are added to the Squally/Resources/ directory. #
###################################################################################

from os import listdir
from os import path
from os.path import isfile, join, splitext, abspath, realpath, basename, relpath
import os

outputHeader = "Source/Resources.h"
outputClass = "Source/Resources.cpp"

extensions = (
	'.png',
	'.jpg',
	'.bmp',
	'.tif', 
	'.ttf',
	'.frag',
	'.vert', 
	'.mp3', 
	'.wav', 
	'.plist',
	'.json',
	'.tmx',
	'.scml'
)

resourcePath = abspath(join(join(realpath(__file__), ".."), "Resources"))
files = []

for extension in extensions:
	for root, dirnames, filenames in os.walk(resourcePath):
		for filename in filenames:
			if filename.lower().endswith(extension):
				files.append(join(root, filename))
				continue
			
with open(outputHeader,'w') as h, open(outputClass,'w') as cpp:

	warning = ( "///////////////////////////////////////////////////////////////////////////////" + "\n" +
		"// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateResources.py TO GENERATE THIS FILE //" + "\n" +
		"///////////////////////////////////////////////////////////////////////////////" + "\n")

	h.write(warning)
	h.write("#pragma once" + "\n");
	h.write("#include <string>" + "\n");
	h.write("\n");
	h.write("class Resources" + "\n");
	h.write("{" + "\n");
	h.write("public:" + "\n");

	cpp.write(warning);
	cpp.write("\n");
	cpp.write("#pragma init_seg(\".CRT$XCU-010\")" + "\n");
	cpp.write("#include \"Resources.h\"" + "\n");
	cpp.write("#include <string>" + "\n");
	cpp.write("\n");

	for file in files:
		relativeFilePath = relpath(file, resourcePath).replace("\\", "\\\\")
		variableName = relativeFilePath.replace("\\\\", "_").replace(" ", "_").replace("-", "_").replace("(", "_").replace(")", "_")
		variableNameNoExtension = splitext(variableName)[0]
		
		h.write("\tstatic const std::string " + variableNameNoExtension + ";" + "\n");
		cpp.write("const std::string Resources::" + variableNameNoExtension + " = \"" + relativeFilePath + "\";" + "\n")

	h.write("};" + "\n")