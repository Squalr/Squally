#!/usr/bin/env python3

###################################################################################
# This script will generate all Resources.cpp and Resources.h files.              #
# Run this script every time files are added to the Squally/Resources/ directory. #
###################################################################################

from os import listdir
from os import path
from os.path import isfile, join, splitext, abspath, realpath, basename, relpath
import os
import re
import sys

def main():
	continueStr = "n"

	print("This will generate all resource paths and will result in a large build time. Continue (y/*)?")

	if (sys.version_info > (3, 0)):
		continueStr = input()
	else:
		continueStr = raw_input()
	
	if (continueStr != "y"):
		print("Script canceled by user")
		return False

	print("Generating resource paths...")
	
	# BackgroundResources
	createResourceFile("BackgroundResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Platformer/Backgrounds")

	# DecorResources
	createResourceFile("DecorResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Platformer/Decor")

	# EntityResources
	createResourceFile("EntityResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Platformer/Entities")

	# IsometricEntityResources
	createResourceFile("IsometricEntityResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Isometric/Entities")

	# HexusResources
	createResourceFile("HexusResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Hexus")

	# PointerTraceResources
	createResourceFile("PointerTraceResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "PointerTrace")

	# CipherResources
	createResourceFile("CipherResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Cipher")

	# ObjectResources
	createResourceFile("ObjectResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Platformer/Objects")

	# ItemResources
	createResourceFile("ItemResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Platformer/Items")

	# FXResources
	createResourceFile("FXResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Platformer/FX")

	# IsometricObjectResources
	createResourceFile("IsometricObjectResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Isometric/Objects")

	# TerrainResources
	createResourceFile("TerrainResources", (
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Platformer/Terrain")

	# TextureResources
	createResourceFile("TextureResources", (
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Platformer/Textures")

	# CutsceneResources
	createResourceFile("CutsceneResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "Cutscenes")

	# UIResources
	createResourceFile("UIResources", (
		'.scml',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "UI")
	
	# ShaderResources
	createResourceFile("ShaderResources", (
		'.frag',
		'.vert',
	), "Shaders")

	# MusicResources
	createResourceFile("MusicResources", (
		'.ogg',
		'.wav',
	), "Music")

	# SoundResources
	createResourceFile("SoundResources", (
		'.ogg',
		'.wav',
	), "Sounds")

	# MapResources
	createResourceFile("MapResources", (
		'.tmx',
		'.png',
	), "Platformer/Maps")

	# IsometricMapResources
	createResourceFile("IsometricMapResources", (
		'.tmx',
		'.png',
	), "Isometric/Maps")

	# ParticleResources
	createResourceFile("ParticleResources", (
		'.plist',
	), "Particles")

	# FontResources
	createResourceFile("FontResources", (
		'.ttf',
		'.png',
		'.jpg',
		'.bmp',
		'.tif',
	), "UI/Fonts")

	# StringResources
	createResourceFile("StringResources", (
		'.json',
	), "Strings")

	print("Resource generation complete.")
	return True

# TODO: Maybe use this, but this needs some debugging
def natural_sort(l): 
    convert = lambda text: int(text) if text.isdigit() else text.lower()
    alphanum_key = lambda key: [convert(c) for c in re.split('([0-9]+)', key)]
    return sorted(l, key=alphanum_key)

def createResourceFile(outputFileBase, extensions, searchPath):
	projectRoot = abspath(join(realpath(__file__), ".."))

	searchPathPublic = join(projectRoot, "Resources/Public/" + searchPath)
	searchPathPrivate = join(projectRoot, "Resources/Private/" + searchPath)

	generatedClassFolder = "Source/Resources/"
	outputHeader = outputFileBase + ".h"
	outputClass = outputFileBase + ".cpp"
	resourcePath = abspath(join(join(realpath(__file__), ".."), "Resources"))
	files = []

	for extension in extensions:
		for root, dirnames, filenames in os.walk(searchPathPublic):
			for filename in filenames:
				if filename.lower().endswith(extension):
					files.append((join(root, filename), searchPathPublic))
					continue
		for root, dirnames, filenames in os.walk(searchPathPrivate):
			for filename in filenames:
				if filename.lower().endswith(extension):
					files.append((join(root, filename), searchPathPrivate))
					continue

	# TODO: Windows/OSX prioritize underscores vs alphanumeric differently. Should probably do a custom sort for consistency.
	files.sort()
			
	with open(generatedClassFolder + outputHeader,'w+') as h, open(generatedClassFolder + outputClass,'w+') as cpp:

		warning = ( "////////////////////////////////////////////////////////////////////////////////////////////" + "\n" +
			"// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateResources.py TO GENERATE THIS FILE //" + "\n" +
			"////////////////////////////////////////////////////////////////////////////////////////////" + "\n")

		h.write(warning)
		h.write("#pragma once" + "\n");
		h.write("#include <string>" + "\n");
		h.write("\n");
		#h.write("class " + outputFileBase + "\n");
		h.write("namespace " + outputFileBase + "\n");
		h.write("{" + "\n");
		# h.write("public:" + "\n");

		cpp.write(warning);
		cpp.write("\n");
		cpp.write("#include \"" + outputHeader + "\"" + "\n");
		cpp.write("#include <string>" + "\n");
		cpp.write("\n");

		for file in files:
			resourceRelativeFilePath = relpath(file[0], resourcePath).replace("\\", "/")
			searchRelativeFilePath = relpath(file[0], file[1]).replace("\\", "/")

			variableName = searchRelativeFilePath \
				.replace("/", "_") \
				.replace(" ", "_") \
				.replace("+", "_") \
				.replace("@", "_") \
				.replace("-", "_") \
				.replace("(", "_") \
				.replace(")", "_")
			variableNameNoExtension = splitext(variableName)[0]
		
			h.write("\textern const std::string " + variableNameNoExtension + ";" + "\n");
			cpp.write("const std::string " + outputFileBase + "::" + variableNameNoExtension + " = \"" + resourceRelativeFilePath + "\";" + "\n")

		h.write("};" + "\n")

if __name__ == '__main__':
    if main():
		# Upon successful regen, call the CopyResources script.
		# We defer the import to CopyResourcces, so that if a nested import is missing, it will not effect this script
        import CopyResources
        CopyResources.main()