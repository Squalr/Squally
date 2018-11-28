###################################################################################
# This script will generate all Resources.cpp and Resources.h files.              #
# Run this script every time files are added to the Squally/Resources/ directory. #
###################################################################################

from os import listdir
from os import path
from os.path import isfile, join, splitext, abspath, realpath, basename, relpath
import os

def main():
	# BackgroundResources
	createResourceFile("BackgroundResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Resources/Gameplay/Platformer/Backgrounds")

	# DecorResources
	createResourceFile("DecorResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Resources/Gameplay/Platformer/Decor")

	# EntityResources
	createResourceFile("EntityResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Resources/Gameplay/Platformer/Entities")

	# HexusResources
	createResourceFile("HexusResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Resources/Gameplay/Hexus")

	# ObjectResources
	createResourceFile("ObjectResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Resources/Gameplay/Platformer/Objects")

	# CutsceneResources
	createResourceFile("CutsceneResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Resources/Cutscenes")

	# UIResources
	createResourceFile("UIResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Resources/UI")
	
	# ShaderResources
	createResourceFile("ShaderResources", (
		'.frag',
		'.vert',
	), "Resources/Shaders")

	# MusicResources
	createResourceFile("MusicResources", (
		'.mp3',
		'.wav',
	), "Resources/Music")

	# SoundResources
	createResourceFile("SoundResources", (
		'.mp3',
		'.wav',
	), "Resources/Sounds")

	# MapResources
	createResourceFile("MapResources", (
		'.tmx',
		'.png',
	), "Resources/Gameplay/Platformer/Maps")

	# ParticleResources
	createResourceFile("ParticleResources", (
		'.plist',
	), "Resources/Particles")

	# FontResources
	createResourceFile("FontResources", (
		'.ttf',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Resources/UI/Fonts")

	# StringResources
	createResourceFile("StringResources", (
		'.json',
	), "Resources/Strings")

def createResourceFile(outputFileBase, extensions, searchPath = "Resources"):
	pathRoot = "Source/Resources/"
	outputHeader = outputFileBase + ".h"
	outputClass = outputFileBase + ".cpp"
	resourcePath = abspath(join(join(realpath(__file__), ".."), "Resources"))
	searchPath = abspath(join(join(realpath(__file__), ".."), searchPath))
	files = []

	for extension in extensions:
		for root, dirnames, filenames in os.walk(searchPath):
			for filename in filenames:
				if filename.lower().endswith(extension):
					files.append(join(root, filename))
					continue

	files.sort()
			
	with open(pathRoot + outputHeader,'w+') as h, open(pathRoot + outputClass,'w+') as cpp:

		warning = ( "////////////////////////////////////////////////////////////////////////////////////////////" + "\n" +
			"// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateResources.py TO GENERATE THIS FILE //" + "\n" +
			"////////////////////////////////////////////////////////////////////////////////////////////" + "\n")

		h.write(warning)
		h.write("#pragma once" + "\n");
		h.write("#include <string>" + "\n");
		h.write("\n");
		h.write("class " + outputFileBase + "\n");
		h.write("{" + "\n");
		h.write("public:" + "\n");

		cpp.write(warning);
		cpp.write("\n");
		cpp.write("#include \"" + outputHeader + "\"" + "\n");
		cpp.write("#include <string>" + "\n");
		cpp.write("\n");

		for file in files:
			resourceRelativeFilePath = relpath(file, resourcePath).replace("\\", "/")
			searchRelativeFilePath = relpath(file, searchPath).replace("\\", "/")
			variableName = searchRelativeFilePath.replace("/", "_").replace(" ", "_").replace("+", "_").replace("-", "_").replace("(", "_").replace(")", "_")
			variableNameNoExtension = splitext(variableName)[0]
		
			h.write("\tstatic const std::string " + variableNameNoExtension + ";" + "\n");
			cpp.write("const std::string " + outputFileBase + "::" + variableNameNoExtension + " = \"" + resourceRelativeFilePath + "\";" + "\n")

		h.write("};" + "\n")

if __name__ == '__main__':
    main()