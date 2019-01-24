from os import listdir
from os import path
from os.path import isfile, join, splitext, abspath, realpath, basename, relpath
import json
import os
import re

def main():
	entityData = parseEntityFile(abspath(join(join(realpath(__file__), ".."), "Entities.json")))
	generateDeserializationCode(entityData)

def generateDeserializationCode(entityData):
	deserializerClass = abspath(join(join(realpath(__file__), ".."), "../../Source/Entities/Platformer/PlatformerEntityDeserializer.cpp"))
	
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
			generatedContent += "\t\t" + "if (name == " + nextEntity["MapKey"] + ")\n"
			generatedContent += "\t\t" + "{\n"
			generatedContent += "\t\t\t" + "newEntity = " + nextEntity["EntityName"] + "::deserialize(&properties);\n"
			generatedContent += "\t\t" + "}\n"
		
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
	entityHealth = str(entityData["Health"])
	entitySpecial = str(entityData["Special"])
	entityEnvironment = entityData["Environment"]
	
	# Construct variables from parsed data
	if entityType == "Enemy":
		entityPrefix = "Enemies"
		entityCollisionType = "Enemy"
		entityBase = "PlatformerEnemy"
		entityBasePath = "Entities/Platformer/PlatformerEnemy.h"
	elif entityType == "Player":
		entityPrefix = "Squally"
		entityCollisionType = "Player"
		entityBase = "PlatformerEntity"
		entityBasePath = "Entities/Platformer/PlatformerEntity.h"
	elif entityType == "Helper":
		entityPrefix = "Helpers"
		entityCollisionType = "FriendlyNpc"
		entityBase = "PlatformerEntity"
		entityBasePath = "Entities/Platformer/PlatformerEntity.h"
	elif entityType == "Npc":
		entityPrefix = "Npcs"
		entityCollisionType = "FriendlyNpc"
		entityBase = "NpcBase"
		entityBasePath = "Entities/Platformer/NpcBase.h"
	elif entityType == "Misc":
		entityPrefix = "Misc"
		entityCollisionType = "FriendlyNpc"
		entityBase = "PlatformerEntity"
		entityBasePath = "Entities/Platformer/PlatformerEntity.h"
	else:
		print("unknown entity type: " + entityType)
		return {}
	
	mapKeyName = "-".join(filter(None, re.split("([A-Z][^A-Z]*)", entityName))).lower()
	pathRoot = ("Source/Entities/Platformer/" + entityPrefix + "/" + entityEnvironment).rstrip("/") + "/"
	animationFile = "Resources/Platformer/Entities/" + entityPrefix + "/" + "entityName"
	outputHeader = entityName + ".h"
	outputClass = entityName + ".cpp"
	templateOutputHeader = abspath(join(join(realpath(__file__), ".."), "Entities.h.template"))
	templateOutputClass = abspath(join(join(realpath(__file__), ".."), "Entities.cpp.template"))
	
	os.makedirs(pathRoot, exist_ok=True)
	with open(pathRoot + outputHeader,'w+') as h, open(pathRoot + outputClass,'w+') as cpp, open(templateOutputHeader,'r') as hTemplate, open(templateOutputClass,'r') as cppTemplate:
		
		def parseTemplate(template):
			templateData = template.read()
			templateData = templateData.replace("{{EntityName}}", entityName).replace("{{EntityBasePath}}", entityBasePath).replace("{{EntityBase}}", entityBase).replace("{{EntityType}}", entityType).replace("{{EntityEnvironment}}", entityEnvironment).replace("{{EntityPrefix}}", entityPrefix).replace("{{EntityCollisionType}}", entityCollisionType).replace("{{MapKeyName}}", mapKeyName).replace("{{EntityScale}}", entityScale).replace("{{EntityWidth}}", entitySize["Width"]).replace("{{EntityHeight}}", entitySize["Height"]).replace("{{EntityOffsetX}}", entityOffset["X"]).replace("{{EntityOffsetY}}", entityOffset["Y"]).replace("{{EntityHealth}}", entityHealth).replace("{{EntitySpecial}}", entitySpecial)
			
			if entityEnvironment == "":
				templateData = templateData.replace("{{EnvironmentUnderscore}}", "");
			else:
				templateData = templateData.replace("{{EnvironmentUnderscore}}", "_");
			
			return templateData
			
		h.write(parseTemplate(hTemplate))
		cpp.write(parseTemplate(cppTemplate))
	
	return {
		"EntityName": entityName,
		"MapKey": entityName + "::" + "MapKey" + entityName,
		"Include": ("#include \"Entities/Platformer/" + entityPrefix + "/" + entityEnvironment).rstrip("/") + "/" + outputHeader + "\""
	}

def replaceTextBetween(delimeterA, delimterB, contents, innerContent):
	contentsPrefix = contents.split(delimeterA)[0]
	contentsSuffix = contents.split(delimterB)[1]
	
	return contentsPrefix + delimeterA + innerContent + delimterB + contentsSuffix
	
if __name__ == '__main__':
    main()
