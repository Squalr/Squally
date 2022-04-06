#!/usr/bin/env python3

###################################################################################
# This script will generate the entity list in PlatformerEntities.h               #
###################################################################################

from os import listdir
from os import path
from os.path import isfile, join, splitext, abspath, relpath, realpath, basename, relpath
import os

outfile = "PlatformerEntities.h"
ignoredFiles = {
	"StatsTables.h",
	"PlatformerEnemy.h",
	"PlatformerEntities.h",
	"PlatformerEntity.h",
	"PlatformerFriendly.h",
	"PlatformerHelper.h",
}

def main():
	generateEntityList()

def generateEntityList():
	# Get source/header files
	currentPath = os.getcwd() 
	hFiles = []

	for root, dirnames, filenames in os.walk(currentPath):
		for filename in filenames:
			pathStr = join(relpath(root, currentPath), filename).replace("\\", "/").lstrip(".").lstrip("/")
			if filename.lower().endswith("h") and not filename in ignoredFiles:
				print(pathStr)
				hFiles.append(pathStr)
				continue

	hFiles.sort()

	with open(outfile, "w") as manifest:
		manifest.write('#pragma once\n\n')
		for filename in hFiles:
			manifest.write('#include "' + filename + '"\n')

if __name__ == '__main__':
    main()
