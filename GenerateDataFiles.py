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
	enemyData = parseEntityFile(abspath(join(join(realpath(__file__), ".."), "Data/Enemies.json")))
	npcData = parseEntityFile(abspath(join(join(realpath(__file__), ".."), "Data/Npcs.json")))
	
	entityData = enemyData + npcData
	generateDeserializationCode(entityData)

def generateDeserializationCode(entityData):
	deserializerClass = abspath(join(join(realpath(__file__), ".."), "Source/Entities/Platformer/PlatformerEntityDeserializer.cpp"))
	firstElement = True
	
	with open(deserializerClass,'r+') as contentReader:
		includesPrefixDelimiter = "////V////V////V////V////V////V////V/"
		includesSuffixDelimiter = "////Y////Y////Y////Y////Y////Y////Y/"
		prefixDelimiter = "////X////X////X////X////X////X////X/"
		suffixDelimiter = "////O////O////O////O////O////O////O/"
		contents = contentReader.read()
		
		generatedIncludes = "\n\n"
		
		for nextEntity in entityData:
			generatedIncludes += nextEntity["Include"] + "\n"
		
		contents = replaceTextBetween(includesPrefixDelimiter, includesSuffixDelimiter, contents, generatedIncludes + "\n")
		generatedContent = "\n\n"
		
		for nextEntity in entityData:
			generatedContent += "\t\t" + ("" if firstElement else "else ") + "if (name == " + nextEntity["MapKey"] + ")\n"
			generatedContent += "\t\t" + "{\n"
			generatedContent += "\t\t\t" + "newEntity = " + nextEntity["EntityName"] + "::deserialize(&properties);\n"
			generatedContent += "\t\t" + "}\n"
			firstElement = False
		
		contents = replaceTextBetween(prefixDelimiter, suffixDelimiter, contents, generatedContent + "\n\t\t")
		
		with open(deserializerClass,'w+') as contentWriter:
			contentWriter.write(contents)

def parseEntityFile(entityDataPath):
	entityData = []
	
	with open(entityDataPath, 'r') as dataFile:
		entityDictionary = json.load(dataFile)
		
	for entityName in entityDictionary:
		entityData.append(parseEntity(entityName, entityDictionary[entityName]))
	
	return entityData
	
def parseEntity(entityName, entityData):
	# Load data
	entityType = entityData["Type"]
	entityScale = entityData["Scale"]
	entitySize = entityData["Size"]
	entityOffset = entityData["Offset"]
	
	# Construct variables from parsed data
	if entityType == "Enemy":
		entityPath = "Enemies"
		entityCollisionType = "Enemy"
		entityBase = "PlatformerEnemy"
		entityBasePath = "Entities/Platformer/PlatformerEnemy.h"
	elif entityType == "Player":
		entityPath = "Squally"
		entityCollisionType = "Player"
		entityBase = "PlatformerEntity"
		entityBasePath = "Entities/Platformer/PlatformerEntity.h"
	elif entityType == "Helper":
		entityPath = "Helpers"
		entityCollisionType = "FriendlyNpc"
		entityBase = "PlatformerEntity"
		entityBasePath = "Entities/Platformer/PlatformerEntity.h"
	elif entityType == "Npc":
		entityPath = "Npcs"
		entityCollisionType = "FriendlyNpc"
		entityBase = "NpcBase"
		entityBasePath = "Entities/Platformer/Npcs/NpcBase.h"
	elif entityType == "Misc":
		entityPath = "Misc"
		entityCollisionType = "FriendlyNpc"
		entityBase = "PlatformerEntity"
		entityBasePath = "Entities/Platformer/PlatformerEntity.h"
	
	mapKeyName = "-".join(filter(None, re.split("([A-Z][^A-Z]*)", entityName))).lower()
	pathRoot = "Source/Entities/Platformer/" + entityPath + "/"
	animationFile = "Resources/Platformer/Entities/" + entityPath + "/" + "entityName"
	outputHeader = entityName + ".h"
	outputClass = entityName + ".cpp"
	templateOutputHeader = abspath(join(join(realpath(__file__), ".."), "Data/Entities.h.template"))
	templateOutputClass = abspath(join(join(realpath(__file__), ".."), "Data/Entities.cpp.template"))
	
	# Todo: create file if does not exist, and use r+ instead of w+, and perserve the "NO OVERWRITE" zone
	
	with open(pathRoot + outputHeader,'w+') as h, open(pathRoot + outputClass,'w+') as cpp, open(templateOutputHeader,'r') as hTemplate, open(templateOutputClass,'r') as cppTemplate:
		
		def parseTemplate(template):
			templateData = template.read()
			return templateData.replace("{{EntityName}}", entityName).replace("{{EntityBasePath}}", entityBasePath).replace("{{EntityBase}}", entityBase).replace("{{EntityType}}", entityType).replace("{{EntityPath}}", entityPath).replace("{{EntityCollisionType}}", entityCollisionType).replace("{{MapKeyName}}", mapKeyName).replace("{{EntityScale}}", entityScale).replace("{{EntityWidth}}", entitySize["Width"]).replace("{{EntityHeight}}", entitySize["Height"]).replace("{{EntityOffsetX}}", entityOffset["X"]).replace("{{EntityOffsetY}}", entityOffset["Y"])
		
		h.write(parseTemplate(hTemplate))
		cpp.write(parseTemplate(cppTemplate))
	
	return {
		"EntityName": entityName,
		"MapKey": entityName + "::" + "MapKey" + entityName,
		"Include": "#include \"Entities/Platformer/" + entityPath + "/" + outputHeader + "\""
	}

def replaceTextBetween(delimeterA, delimterB, contents, innerContent):
	contentsPrefix = contents.split(delimeterA)[0]
	contentsSuffix = contents.split(delimterB)[1]
	
	return contentsPrefix + delimeterA + innerContent + delimterB + contentsSuffix
	
if __name__ == '__main__':
    main()