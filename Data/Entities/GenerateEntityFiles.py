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

		pathSplit = relpath(entityDataPath).split("/")

		# Construct meta-variables
		entityData["Environment"] = pathSplit[len(pathSplit) - 3]
		entityData["Prefix"] = pathSplit[len(pathSplit) - 2]
		entityData["Name"] = pathSplit[len(pathSplit) - 1][:-len(".json")]

		entityData["MapKeyName"] = "-".join(filter(None, re.split("([A-Z][^A-Z]*)", entityData["Name"]))).lower()
		entityData["HexusSaveKey"] = "HEXUS_OPPONENT_SAVE_KEY_" + "_".join(filter(None, re.split("([A-Z][^A-Z]*)", entityData["Name"]))).upper()

		if entityData["Environment"] == "BalmerPeaks":
			entityData["Hexus"]["CardStyle"] = "Water"
		elif entityData["Environment"] == "CastleValgrind":
			entityData["Hexus"]["CardStyle"] = "Air"
		elif entityData["Environment"] == "DaemonsHallow":
			entityData["Hexus"]["CardStyle"] = "Fire"
		elif entityData["Environment"] == "EndianForest":
			entityData["Hexus"]["CardStyle"] = "Earth"
		elif entityData["Environment"] == "LambdaCrypts":
			entityData["Hexus"]["CardStyle"] = "Shadow"
		elif entityData["Environment"] == "SeaSharpCaverns":
			entityData["Hexus"]["CardStyle"] = "Earth"
		elif entityData["Environment"] == "UnderflowRuins":
			entityData["Hexus"]["CardStyle"] = "Light"
		elif entityData["Environment"] == "VoidStar":
			entityData["Hexus"]["CardStyle"] = "Shadow"
		
		if not "PuzzleData" in entityData["Hexus"]:
			entityData["IsHexusPuzzle"] = False
			entityData["Hexus"]["PuzzleData"] = "nullptr"
		else:
			entityData["IsHexusPuzzle"] = True
			entityData["Hexus"]["PuzzleData"] = buildPuzzleContent(entityData)

		# Reformat preset card list to match C++ needs
		presetCards = ""

		for presetCard in entityData["Hexus"]["MatchData"]["PresetCards"]:
			presetCards += "\t\t\t\tCardList::getInstance()->cardListByName.at(CardKeys::" + presetCard + "),\n"

		entityData["Hexus"]["MatchData"]["PresetCards"] = presetCards

		# Evaluate strength equations
		entityData["Hexus"]["MatchData"]["Strength"] = "%.3f"%(eval(entityData["Hexus"]["MatchData"]["Strength"].replace("f", ""))) + "f"

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
			print(entityDataPath)
			print("unknown entity type: " + entityData["Prefix"])
			return {}
		
		return entityData

	return []

def buildPuzzleContent(entityData):
	puzzleDataTemplateFile = abspath(join(join(realpath(__file__), ".."), "PuzzleData.template"))

	def buildCardList(cardList):
		cppCardList = ""

		for card in cardList:
			cppCardList += "CardList::getInstance()->cardListByName.at(CardKeys::" + card + "),\n"
			pass
		
		return cppCardList.rstrip()
	
	if not entityData["Hexus"]["PuzzleData"]["TutorialKey"]:
		entityData["Hexus"]["PuzzleData"]["TutorialKey"] = "StateOverride::TutorialMode::NoTutorial"

	with open(puzzleDataTemplateFile, "r") as puzzleDataTemplateReader:
		puzzleContent = puzzleDataTemplateReader.read()
		puzzleContent = puzzleContent \
		.replace("{{PlayerLosses}}", entityData["Hexus"]["PuzzleData"]["PlayerLosses"]) \
		.replace("{{EnemyLosses}}", entityData["Hexus"]["PuzzleData"]["EnemyLosses"]) \
		.replace("{{PlayersTurn}}", entityData["Hexus"]["PuzzleData"]["PlayersTurn"]) \
		.replace("{{PlayerPassed}}", entityData["Hexus"]["PuzzleData"]["EnemyPassed"]) \
		.replace("{{EnemyPassed}}", entityData["Hexus"]["PuzzleData"]["EnemyPassed"]) \
		.replace("{{PlayerDeck}}", buildCardList(entityData["Hexus"]["PuzzleData"]["PlayerDeck"])) \
		.replace("{{EnemyDeck}}", buildCardList(entityData["Hexus"]["PuzzleData"]["EnemyDeck"])) \
		.replace("{{PlayerHand}}", buildCardList(entityData["Hexus"]["PuzzleData"]["PlayerHand"])) \
		.replace("{{EnemyHand}}", buildCardList(entityData["Hexus"]["PuzzleData"]["EnemyHand"])) \
		.replace("{{PlayerBinaryCards}}", buildCardList(entityData["Hexus"]["PuzzleData"]["PlayerBinaryCards"])) \
		.replace("{{PlayerDecimalCards}}", buildCardList(entityData["Hexus"]["PuzzleData"]["PlayerDecimalCards"])) \
		.replace("{{PlayerHexCards}}", buildCardList(entityData["Hexus"]["PuzzleData"]["PlayerHexCards"])) \
		.replace("{{EnemyBinaryCards}}", buildCardList(entityData["Hexus"]["PuzzleData"]["EnemyBinaryCards"])) \
		.replace("{{EnemyDecimalCards}}", buildCardList(entityData["Hexus"]["PuzzleData"]["EnemyDecimalCards"])) \
		.replace("{{EnemyHexCards}}", buildCardList(entityData["Hexus"]["PuzzleData"]["EnemyHexCards"]))\
		.replace("{{TutorialKey}}", entityData["Hexus"]["PuzzleData"]["TutorialKey"])

		return puzzleContent
	return ""
	
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
				.replace("{{EntityHealth}}", entityData["Health"]) \
				.replace("{{EntitySpecial}}", entityData["Special"]) \
				.replace("{{EntityAvatarOffsetX}}", entityData["AvatarOffset"]["X"]) \
				.replace("{{EntityAvatarOffsetY}}", entityData["AvatarOffset"]["Y"]) \
				.replace("{{HexusSaveKey}}", entityData["HexusSaveKey"]) \
				.replace("{{HexusStrategy}}", entityData["Hexus"]["MatchData"]["Strategy"]) \
				.replace("{{HexusStrength}}", entityData["Hexus"]["MatchData"]["Strength"]) \
				.replace("{{HexusDeckSize}}", entityData["Hexus"]["MatchData"]["DeckSize"]) \
				.replace("{{HexusPresetCards}}", entityData["Hexus"]["MatchData"]["PresetCards"]) \
				.replace("{{HexusCardStyle}}", entityData["Hexus"]["CardStyle"]) \
				.replace("{{HexusPuzzleData}}", entityData["Hexus"]["PuzzleData"]) \
				.replace("{{HexusFrameOffsetX}}", entityData["Hexus"]["FrameOffset"]["X"]) \
				.replace("{{HexusFrameOffsetY}}", entityData["Hexus"]["FrameOffset"]["Y"])

			if entityData["Environment"] == "":
				templateData = templateData.replace("{{EnvironmentUnderscore}}", "");
			else:
				templateData = templateData.replace("{{EnvironmentUnderscore}}", "_");
			
			return templateData
			
		hContent = parseTemplate(hTemplate)
		cppContent = parseTemplate(cppTemplate)
		
		hContent = replaceTextBetween(hPrefixA, hSuffixA, hContent, hUserContentA + "\n\n")
		hContent = replaceTextBetween(hPrefixB, hSuffixB, hContent, hUserContentB + "\n\t\n\t")
		hContent = replaceTextBetween(hPrefixC, hSuffixC, hContent, hUserContentC + "\n\t\n\t")
		cppContent = replaceTextBetween(cppPrefixA, cppSuffixA, cppContent, cppUserContentA + "\n\n")
		cppContent = replaceTextBetween(cppPrefixB, cppSuffixB, cppContent, cppUserContentB + "\n\t\n\t")
		cppContent = replaceTextBetween(cppPrefixC, cppSuffixC, cppContent, cppUserContentC + "\n\n")
			
		h.write(hContent)
		cpp.write(cppContent)

def generateHexusMenuCode(allEntityData):
	menuRoot = abspath(join(join(realpath(__file__), ".."), "../../Source/Scenes/Hexus/Menus/OpponentSelect/"))
	puzzleMenuRoot = abspath(join(join(realpath(__file__), ".."), "../../Source/Scenes/Hexus/Menus/PuzzleSelect/"))

	hTemplateFile = abspath(join(join(realpath(__file__), ".."), "HexusOpponentMenu.h.template"))
	cppTemplateFile = abspath(join(join(realpath(__file__), ".."), "HexusOpponentMenu.cpp.template"))

	sortedEntities = {}

	for entity in allEntityData:
		if entity["Type"] != "Misc":
			if not entity["Environment"] in sortedEntities:
				sortedEntities[entity["Environment"]] = []
			
			sortedEntities[entity["Environment"]].append(entity)

	with open(hTemplateFile, "r+") as hTemplateReader, open(cppTemplateFile, "r+") as cppTemplateReader:
		hTemplateContent = hTemplateReader.read()
		cppTemplateContent = cppTemplateReader.read()

		for environment in sortedEntities:
			entities = sortedEntities[environment]
			
			menuName = "HexusOpponentMenu" + environment
			menuNamePuzzle = "HexusOpponentMenu" + environment + "Puzzle"
			hOutFile = menuRoot + "/" + environment + "/" + menuName + ".h"
			cppOutFile = menuRoot + "/" + environment + "/" + menuName + ".cpp"
			hOutFilePuzzle = puzzleMenuRoot + "/" + environment + "/" + menuNamePuzzle + ".h"
			cppOutFilePuzzle = puzzleMenuRoot + "/" + environment + "/" + menuNamePuzzle + ".cpp"
			
			if sys.version_info >= (3, 0):
				os.makedirs(dirname(cppOutFile), exist_ok=True)
				os.makedirs(dirname(cppOutFilePuzzle), exist_ok=True)
			else:
				# Python 2 support, although it creates a race condition
				if not os.path.exists(dirname(cppOutFile)):
					os.makedirs(dirname(cppOutFile))
				if not os.path.exists(dirname(cppOutFilePuzzle)):
					os.makedirs(dirname(cppOutFilePuzzle))

			hContent = hTemplateContent
			cppContent = cppTemplateContent
			hContentPuzzle = hTemplateContent
			cppContentPuzzle = cppTemplateContent
			generatedEnemyList = ""
			generatedIncludes = ""
			generatedPuzzleEnemyList = ""
			generatedPuzzleIncludes = ""

			for nextEntity in entities:
				if not nextEntity["IsHexusPuzzle"] and nextEntity["Type"] == "Npc":
					generatedIncludes += ("#include \"Entities/Platformer/" + nextEntity["Prefix"] + "/" + nextEntity["Environment"]).rstrip("/") + "/" + nextEntity["Name"] + ".h\"" + "\n"
					generatedEnemyList += "\t" + "this->opponents.push_back(HexusOpponentPreview::create(" + nextEntity["Name"] + "::getHexusOpponentData()));\n"
				elif nextEntity["IsHexusPuzzle"] and nextEntity["Type"] == "Enemy":
					generatedPuzzleIncludes += ("#include \"Entities/Platformer/" + nextEntity["Prefix"] + "/" + nextEntity["Environment"]).rstrip("/") + "/" + nextEntity["Name"] + ".h\"" + "\n"
					generatedPuzzleEnemyList += "\t" + "this->opponents.push_back(HexusOpponentPreview::create(" + nextEntity["Name"] + "::getHexusOpponentData()));\n"
			
			cppContent = cppContent.replace("{{Environment}}", environment) \
				.replace("{{HexusOpponentIncludes}}", generatedIncludes) \
				.replace("{{HexusOpponents}}", generatedEnemyList) \
				.replace("{{MenuName}}", menuName) \
				.replace("{{PuzzleTag}}", "")
			hContent = hContent.replace("{{MenuName}}", menuName)

			cppContentPuzzle = cppContentPuzzle.replace("{{Environment}}", environment) \
				.replace("{{HexusOpponentIncludes}}", generatedPuzzleIncludes) \
				.replace("{{HexusOpponents}}", generatedPuzzleEnemyList) \
				.replace("{{MenuName}}", menuNamePuzzle) \
				.replace("{{PuzzleTag}}", "Puzzle")
			hContentPuzzle = hContentPuzzle.replace("{{MenuName}}", menuNamePuzzle)

			with open(hOutFile, "w+") as hWriter, open(cppOutFile, "w+") as cppWriter, open(hOutFilePuzzle, "w+") as hWriterPuzzle, open(cppOutFilePuzzle, "w+") as cppWriterPuzzle:
				hWriter.write(hContent)
				cppWriter.write(cppContent)
				hWriterPuzzle.write(hContentPuzzle)
				cppWriterPuzzle.write(cppContentPuzzle)

def generateEntityDeserializationCode(allEntityData):
	deserializerClass = abspath(join(join(realpath(__file__), ".."), "../../Source/Entities/Platformer/PlatformerEntityDeserializer.cpp"))
	contents = ""

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
	if not delimeterA in contents or delimeterB in contents:
		return ""
	return contents.split(delimeterA)[1].split(delimeterB)[0]
	
if __name__ == "__main__":
    main()
