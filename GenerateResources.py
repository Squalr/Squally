#!/usr/bin/env python3

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
		'.mp3',
		'.wav',
	), "Music")

	# SoundResources
	createResourceFile("SoundResources", (
		'.mp3',
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
    main()