####################################################################################
# This script will (in a hacky way) parse all of the existing entity cpp files and #
# dump their unique data to a json file in the same directory as this script.      #
####################################################################################

from os import listdir
from os import path
from os.path import isfile, join, splitext, abspath, realpath, basename, relpath
import json
import os

def main():
	dumpEntityData()
	
def dumpEntityData():
	searchPath = abspath(join(join(realpath(__file__), ".."), "../Source/Entities/Platformer/"))
	files = []

	for root, dirnames, filenames in os.walk(searchPath):
		for filename in filenames:
			if filename.lower().endswith(".cpp"):
				files.append(join(root, filename))
				continue

	files.sort()
	
	extractedData = {};
	
	with open("dump.json", 'w+') as dumpFile:
		for file in files:
			with open(file, 'r') as nextFile:
				originalContents = nextFile.read()
				
				if "(initProperties,\n" not in originalContents:
					continue
				
				contents = originalContents.split("(initProperties,\n")[1].strip().split("{")[0].strip()
				contents = contents.split("\n")
				
				for next in contents:
					print(next)
				
				enemyName = originalContents.split("::~")[1].split("(")[0]
				
				print("------")
				print(file)
				print(contents)
				
				collisionType = contents[1].split("::")[1].replace(",", "").strip()
				type = collisionType.replace("FriendlyNpc", "Npc")
				sizeX = contents[2].split("(")[1].split(",")[0].strip()
				sizeY = contents[2].split(",")[1].split(")")[0].strip()
				scale = contents[3].replace(",", "").strip()
				offsetX = contents[4].split("(")[1].split(",")[0].strip()
				offsetY = contents[4].split(",")[1].split(")")[0].strip()
				
				extractedData[enemyName] = {
					"Type": collisionType,
					"Environment": "",
					"Scale": scale,
					"Size": {
						"Width": sizeX,
						"Height": sizeY
					},
					"Offset": {
						"X": offsetX,
						"Y": offsetY
					}
				}
				
				
		json.dump(extractedData, dumpFile)

if __name__ == '__main__':
    main()