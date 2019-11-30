#!/usr/bin/env python3

import io
import json
import os
import re
import shutil
import sys

from os import listdir
from os import path
from os.path import isfile, dirname, join, splitext, abspath, realpath, basename, relpath

def main():
	generateStringFiles()

def generateStringFiles():
	
	# Delete the existing string folder to force a regen of all contents
	outputPath = abspath(join(realpath(__file__), "../../../Source/Strings/"))
	shutil.rmtree(outputPath, ignore_errors=True)
	os.makedirs(outputPath)

	searchPath = dirname(realpath(__file__))
	files = []

	for root, dirnames, filenames in os.walk(searchPath):
		for filename in filenames:
			if filename.lower().endswith(".json"):
				files.append(join(root, filename))
				continue

	files.sort()
	
	templateOutputHeaderPrefix = abspath(join(join(realpath(__file__), ".."), "Strings.h_prefix.template"))
	templateOutputClassPrefix = abspath(join(join(realpath(__file__), ".."), "Strings.cpp_prefix.template"))
	templateOutputHeader = abspath(join(join(realpath(__file__), ".."), "Strings.h.template"))
	templateOutputClass = abspath(join(join(realpath(__file__), ".."), "Strings.cpp.template"))
	hOutputFile = join(outputPath, "Strings.h")
	cppOutputFile = join(outputPath, "Strings.cpp")
	outputDir = dirname(hOutputFile)

	if sys.version_info >= (3, 0):
		os.makedirs(outputDir, exist_ok=True)
	else:
		# Python 2 support, although it creates a race condition
		if not os.path.exists(outputDir):
			os.makedirs(outputDir)
	
	with open(templateOutputHeaderPrefix,'r') as hPrefixTemplate, open(templateOutputClassPrefix,'r') as cppPrefixTemplate, open(templateOutputHeader,'r') as hTemplate, open(templateOutputClass,'r') as cppTemplate:
		hPrefixTemplateContent = hPrefixTemplate.read();
		cppPrefixTemplateContent = cppPrefixTemplate.read();
		hTemplateContent = hTemplate.read();
		cppTemplateContent = cppTemplate.read();
		
		with open(hOutputFile, 'w+', encoding="utf-8") as hWriter, open(cppOutputFile, 'w+', encoding="utf-8") as cppWriter:
			
			# Writer header
			hWriter.write(hPrefixTemplateContent)
			cppWriter.write(cppPrefixTemplateContent)

			for stringFile in files:
				print(stringFile)
				fileRelative = relpath(stringFile, searchPath).replace("\\", "/")
				className = fileRelative.replace("/", "_").replace(" ", "_").replace("+", "_").replace("-", "_").replace("(", "_").replace(")", "_").replace(".json", "")
				fileName = splitext(basename(stringFile))[0]

				with open(stringFile, 'r', encoding="utf-8") as stringData:
					languageDictionary = json.load(stringData)
					hContent = hTemplateContent.replace("{{ClassName}}", className).replace("{{FileName}}", fileName)
					cppContent = cppTemplateContent.replace("{{ClassName}}", className).replace("{{FileName}}", fileName)
					
					for langKey, value in languageDictionary.items():
						cppContent = cppContent.replace("{{" + langKey + "}}", value)
						
					hContent = hContent.encode("utf-8")
					cppContent = cppContent.encode("utf-8")

					hWriter.write(hContent.decode("utf-8"))
					cppWriter.write(cppContent.decode("utf-8"))
		
if __name__ == '__main__':
    main()
