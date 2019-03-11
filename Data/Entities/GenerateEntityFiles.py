from os import listdir
from os import path
from os.path import isfile, dirname, join, splitext, abspath, realpath, basename, relpath
import json
import os
import re
import sys

def main():
	generateEntityFiles()

def generateEntityFiles():
	searchPath = dirname(realpath(__file__))
	files = []

	# Read all json files under this directory
	for root, dirnames, filenames in os.walk(searchPath):
		for filename in filenames:
			if filename.lower().endswith(".json"):
				files.append(join(root, filename))
				continue

	files.sort()

	allEntityData = []

	# Parse each one and generate the file data
	for entityDataFile in files:
		entityData = parseEntityFile(entityDataFile)

		if entityData:
			generateEntityCode(entityData)
			allEntityData.append(entityData)

	generateEntityDeserializationCode(allEntityData)
	generateHexusMenuCode(allEntityData)

def parseEntityFile(entityDataPath):
	# Load the entity JSON file
	with open(entityDataPath, "r") as dataFile:
		entityData = json.load(dataFile)

		# Construct meta-variables
		entityData["Environment"] = relpath(entityDataPath).split("/")[0]
		entityData["Prefix"] = relpath(entityDataPath).split("/")[1]
		entityData["Name"] = relpath(entityDataPath).split("/")[2][:-len(".json")]
		entityData["MapKeyName"] = "-".join(filter(None, re.split("([A-Z][^A-Z]*)", entityData["Name"]))).lower()
		entityData["HexusSaveKey"] = "HEXUS_OPPONENT_SAVE_KEY_" + "_".join(filter(None, re.split("([A-Z][^A-Z]*)", entityData["Name"]))).upper()

		if entityData["Prefix"] == "Enemies":
			entityData["Type"] = "Enemy"
			entityData["Collision"] = "Enemy"
			entityData["Base"] = "PlatformerEnemy"
			entityData["Path"] = "Entities/Platformer/PlatformerEnemy.h"
		elif entityData["Prefix"] == "Helpers":
			entityData["Type"] = "Helper"
			entityData["Collision"] = "FriendlyNpc"
			entityData["Base"] = "PlatformerEntity"
			entityData["Path"] = "Entities/Platformer/PlatformerEntity.h"
		elif entityData["Prefix"] == "Npcs":
			entityData["Type"] = "Npc"
			entityData["Collision"] = "FriendlyNpc"
			entityData["Base"] = "NpcBase"
			entityData["Path"] = "Entities/Platformer/NpcBase.h"
		elif entityData["Prefix"] == "Misc":
			entityData["Type"] = "Misc"
			entityData["Collision"] = "FriendlyNpc"
			entityData["Base"] = "PlatformerEntity"
			entityData["Path"] = "Entities/Platformer/PlatformerEntity.h"
		else:
			print("unknown entity type: " + entityData["Prefix"])
			return {}
		
		return entityData

	return []
	
def generateEntityCode(entityData):
	pathRoot = abspath(join(join(realpath(__file__), "../../.."), ("Source/Entities/Platformer/" + entityData["Prefix"] + "/" + entityData["Environment"]).rstrip("/"))) + "/"
	outputHeader = entityData["Name"] + ".h"
	outputClass = entityData["Name"] + ".cpp"
	templateOutputHeader = abspath(join(join(realpath(__file__), ".."), "Entities.h.template"))
	templateOutputClass = abspath(join(join(realpath(__file__), ".."), "Entities.cpp.template"))
	
	cppPrefixA = hPrefixA = "////A////A////A////A////A////A////A////A////A////A/"
	cppSuffixA = hSuffixA = "////B////B////B////B////B////B////B////B////B////B/"
	cppPrefixB = hPrefixB = "////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/"
	cppSuffixB = hSuffixB = "////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/"
	cppPrefixC = hPrefixC = "////X////X////X////X////X////X////X////X////X////X/"
	cppSuffixC = hSuffixC = "////O////O////O////O////O////O////O////O////O////O/"
	
	hUserContentA = ""
	hUserContentB = ""
	hUserContentC = ""
	cppUserContentA = ""
	cppUserContentB = ""
	cppUserContentC = ""
	
	# Parse any user code in non-generated sections
	if os.path.isfile(pathRoot + outputHeader) and os.path.isfile(pathRoot + outputClass):
		with open(pathRoot + outputHeader,"r") as h, open(pathRoot + outputClass,"r") as cpp:
			hContent = h.read()
			cppContent = cpp.read()
			hUserContentA = getTextBetween(hPrefixA, hSuffixA, hContent)
			hUserContentB = getTextBetween(hPrefixB, hSuffixB, hContent)
			hUserContentC = getTextBetween(hPrefixC, hSuffixC, hContent)
			cppUserContentA = getTextBetween(cppPrefixA, cppSuffixA, cppContent)
			cppUserContentB = getTextBetween(cppPrefixB, cppSuffixB, cppContent)
			cppUserContentC = getTextBetween(cppPrefixC, cppSuffixC, cppContent)
	
	if sys.version_info >= (3, 0):
		os.makedirs(pathRoot, exist_ok=True)
	else:
		# Python 2 support, although it creates a race condition
		if not os.path.exists(pathRoot):
			os.makedirs(pathRoot)
	with open(pathRoot + outputHeader,"w+") as h, open(pathRoot + outputClass,"w+") as cpp, open(templateOutputHeader,"r") as hTemplate, open(templateOutputClass,"r") as cppTemplate:
		
		def parseTemplate(template):
			templateData = template.read()
			templateData = templateData \
				.replace("{{EntityName}}", entityData["Name"]) \
				.replace("{{EntityBasePath}}", entityData["Path"]) \
				.replace("{{EntityBase}}", entityData["Base"]) \
				.replace("{{EntityType}}", entityData["Type"]) \
				.replace("{{EntityEnvironment}}", entityData["Environment"]) \
				.replace("{{EntityPrefix}}", entityData["Prefix"]) \
				.replace("{{EntityCollisionType}}", entityData["Collision"]) \
				.replace("{{MapKeyName}}", entityData["MapKeyName"]) \
				.replace("{{EntityScale}}", entityData["Scale"]) \
				.replace("{{EntityWidth}}", entityData["Size"]["Width"]) \
				.replace("{{EntityHeight}}", entityData["Size"]["Height"]) \
				.replace("{{EntityOffsetX}}", entityData["Offset"]["X"]) \
				.replace("{{EntityOffsetY}}", entityData["Offset"]["Y"]) \
				.replace("{{EntityHealth}}", str(entityData["Health"])) \
				.replace("{{EntitySpecial}}", str(entityData["Special"])) \
				.replace("{{EntityFrameOffsetX}}", str(entityData["FrameOffset"]["X"])) \
				.replace("{{EntityFrameOffsetY}}", str(entityData["FrameOffset"]["Y"])) \
				.replace("{{HexusSaveKey}}", entityData["HexusSaveKey"] )
			
			if entityData["Environment"] == "":
				templateData = templateData.replace("{{EnvironmentUnderscore}}", "");
			else:
				templateData = templateData.replace("{{EnvironmentUnderscore}}", "_");
			
			return templateData
			
		hContent = parseTemplate(hTemplate)
		cppContent = parseTemplate(cppTemplate)
		
		hContent = replaceTextBetween(hPrefixA, hSuffixA, hContent, hUserContentA)
		hContent = replaceTextBetween(hPrefixB, hSuffixB, hContent, hUserContentB)
		hContent = replaceTextBetween(hPrefixC, hSuffixC, hContent, hUserContentC)
		cppContent = replaceTextBetween(cppPrefixA, cppSuffixA, cppContent, cppUserContentA)
		cppContent = replaceTextBetween(cppPrefixB, cppSuffixB, cppContent, cppUserContentB)
		cppContent = replaceTextBetween(cppPrefixC, cppSuffixC, cppContent, cppUserContentC)
			
		h.write(hContent)
		cpp.write(cppContent)

def generateEntityDeserializationCode(allEntityData):
	menuRoot = abspath(join(join(realpath(__file__), ".."), "../../Source/Scenes/Hexus/Menus/OpponentSelect/"))

	cppTemplateFile = "HexusOpponentMenu.cpp.template"
	hTemplateFile = "HexusOpponentMenu.h.template"
	prefixDelimiter = "////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/"
	suffixDelimiter = "////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/"
	includePrefixDelimiter = "////X////X////X////X////X////X////X////X////X////X/"
	includeSuffixDelimiter = "////O////O////O////O////O////O////O////O////O////O/"

	sortedEntities = {}

	for entity in allEntityData:
		if not entity["Environment"] in sortedEntities:
			sortedEntities[entity["Environment"]] = []
		
		sortedEntities[entity["Environment"]].append(entity)

	with open(hTemplateFile, "r+") as hTemplateReader, open(cppTemplateFile, "r+") as cppTemplateReader:
		hTemplateContent = hTemplateReader.read()
		cppTemplateContent = cppTemplateReader.read()

		for environment in sortedEntities:
			entities = sortedEntities[environment]
			menuName = "HexusOpponentMenu" + environment
			hOutFile = menuRoot + "/" + environment + "/" + menuName + ".h"
			cppOutFile = menuRoot + "/" + environment + "/" + menuName + ".cpp"

			if sys.version_info >= (3, 0):
				os.makedirs(dirname(cppOutFile), exist_ok=True)
			else:
				# Python 2 support, although it creates a race condition
				if not os.path.exists(dirname(cppOutFile)):
					os.makedirs(dirname(cppOutFile))

			hContent = hTemplateContent
			cppContent = cppTemplateContent
			generatedEnemyList = "\n\n"
			generatedIncludes = "\n\n"

			for nextEntity in entities:
				generatedIncludes += ("#include \"Entities/Platformer/" + nextEntity["Prefix"] + "/" + nextEntity["Environment"]).rstrip("/") + "/" + nextEntity["Name"] + ".h\"" + "\n"
				generatedEnemyList += "\t" + "this->opponents.push_back(HexusOpponentPreview::create(" + nextEntity["Name"] + "::getHexusOpponentData()));\n"

			cppContent = replaceTextBetween(includePrefixDelimiter, includeSuffixDelimiter, cppContent, generatedIncludes + "\n")
			cppContent = replaceTextBetween(prefixDelimiter, suffixDelimiter, cppContent, generatedEnemyList + "\n\t")
			cppContent = cppContent.replace("{{MenuName}}", menuName)
			hContent = hContent.replace("{{MenuName}}", menuName)

			with open(hOutFile, "w+") as hWriter, open(cppOutFile, "w+") as cppWriter:
				hWriter.write(hContent)
				cppWriter.write(cppContent)

def generateHexusMenuCode(allEntityData):
	deserializerClass = abspath(join(join(realpath(__file__), ".."), "../../Source/Entities/Platformer/PlatformerEntityDeserializer.cpp"))
	
	with open(deserializerClass,"r+") as contentReader:
		includesPrefixDelimiter = "////V////V////V////V////V////V////V/"
		includesSuffixDelimiter = "////Y////Y////Y////Y////Y////Y////Y/"
		prefixDelimiter = "////X////X////X////X////X////X////X/"
		suffixDelimiter = "////O////O////O////O////O////O////O/"
		contents = contentReader.read()
		
		generatedIncludes = "\n\n"
		
		for nextEntity in allEntityData:
			generatedIncludes += ("#include \"Entities/Platformer/" + nextEntity["Prefix"] + "/" + nextEntity["Environment"]).rstrip("/") + "/" + nextEntity["Name"] + ".h\"" + "\n"
		
		contents = replaceTextBetween(includesPrefixDelimiter, includesSuffixDelimiter, contents, generatedIncludes + "\n")
		generatedContent = "\n\n"
		
		for nextEntity in allEntityData:
			generatedContent += "\t\t" + "if (name == " + nextEntity["Name"] + "::" + "MapKey" + nextEntity["Name"] + ")\n"
			generatedContent += "\t\t" + "{\n"
			generatedContent += "\t\t\t" + "newEntity = " + nextEntity["Name"] + "::deserialize(properties);\n"
			generatedContent += "\t\t" + "}\n"
		
		contents = replaceTextBetween(prefixDelimiter, suffixDelimiter, contents, generatedContent + "\n\t\t")
		
		with open(deserializerClass,"w+") as contentWriter:
			contentWriter.write(contents)

def replaceTextBetween(delimeterA, delimeterB, contents, innerContent):
	contentsPrefix = contents.split(delimeterA)[0]
	contentsSuffix = contents.split(delimeterB)[1]
	
	return contentsPrefix + delimeterA + innerContent + delimeterB + contentsSuffix

def getTextBetween(delimeterA, delimeterB, contents):
	return contents.split(delimeterA)[1].split(delimeterB)[0]
	
if __name__ == "__main__":
    main()
