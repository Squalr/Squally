from os import listdir
from os import path
from os.path import isfile, dirname, join, splitext, abspath, realpath, basename, relpath
import json
import os
import re

def main():
	generateStringFiles()

def generateStringFiles():
	searchPath = dirname(realpath(__file__))
	files = []

	for root, dirnames, filenames in os.walk(searchPath):
		for filename in filenames:
			if filename.lower().endswith(".json"):
				files.append(join(root, filename))
				continue

	files.sort()
	
	templateOutputHeader = abspath(join(join(realpath(__file__), ".."), "Strings.h.template"))
	templateOutputClass = abspath(join(join(realpath(__file__), ".."), "Strings.cpp.template"))
	
	with open(templateOutputHeader,'r') as hTemplate, open(templateOutputClass,'r') as cppTemplate:
		hTemplateContent = hTemplate.read();
		cppTemplateContent = cppTemplate.read();
		
		for stringFile in files:
			fileRelative = relpath(stringFile, searchPath)
			outputPath = abspath(dirname(join(join(searchPath, "../../Source/Strings/"), fileRelative)))
			className = splitext(basename(stringFile))[0]
			hOutputFile = join(outputPath, className + ".h")
			cppOutputFile = join(outputPath, className + ".cpp")
			
			os.makedirs(dirname(hOutputFile), exist_ok=True)
			with open(stringFile, 'r', encoding="utf-8") as stringData, open(hOutputFile, 'w+', encoding="utf-8") as hWriter, open(cppOutputFile, 'w+', encoding="utf-8") as cppWriter:
				languageDictionary = json.load(stringData)
				hContent = hTemplateContent.replace("{{ClassName}}", className)
				cppContent = cppTemplateContent.replace("{{ClassName}}", className)
				
				for langKey, value in languageDictionary.items():
					cppContent = cppContent.replace("{{" + langKey + "}}", value)
					
				hWriter.write(hContent)
				cppWriter.write(cppContent)
		
if __name__ == '__main__':
    main()
