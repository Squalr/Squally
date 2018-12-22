###################################################################################
# This script will generate the CMakeLists.txt target files.                      #
# Run this script every time files are added to the Squally/Source/ directory.    #
###################################################################################

from os import listdir
from os import path
from os.path import isfile, join, splitext, abspath, relpath, realpath, basename, relpath
import os

def main():
	generateCmakeFile()
	
def generateCmakeFile():
	cmakeFile = "CMakeLists.txt"
	
	# Get source/header files
	currentPath = realpath(__file__)
	sourcePath = abspath(join(join(currentPath, ".."), "Source"))
	cppFiles = []
	hFiles = []

	for root, dirnames, filenames in os.walk(sourcePath):
		for filename in filenames:
			pathStr = join(relpath(root, currentPath), filename).replace("\\", "/").lstrip(".").lstrip("/")
			
			print(pathStr)
			if filename.lower().endswith("cpp"):
				cppFiles.append(pathStr)
				continue
			if filename.lower().endswith("h"):
				hFiles.append(pathStr)
				continue

	cppFiles.sort()
	hFiles.sort()

	# Update source/header files in the CMakeLists
	with open(cmakeFile,'r+') as contentReader:
		cppPrefixDelimiter = "####X####X####X####X####X####X####X####X####X####X####"
		cppSuffixDelimiter = "####O####O####O####O####O####O####O####O####O####O##"
		hPrefixDelimiter = "####W####W####W####W####W####W####W####W####W####W####"
		hSuffixDelimiter = "####V####V####V####V####V####V####V####V####V####V##"
		cppList = "\n\t".join(cppFiles)
		hList = "\n\t".join(hFiles)
		
		contents = contentReader.read()
		
		contents = replaceTextBetween(cppPrefixDelimiter, cppSuffixDelimiter, contents, "\n\n\t" + cppList + "\n\n\t")
		contents = replaceTextBetween(hPrefixDelimiter, hSuffixDelimiter, contents, "\n\n\t" + hList + "\n\n\t")
		
		with open(cmakeFile,'w+') as contentWriter:
			contentWriter.write(contents)


def replaceTextBetween(delimeterA, delimterB, contents, innerContent):
	contentsPrefix = contents.split(delimeterA)[0]
	contentsSuffix = contents.split(delimterB)[1]
	
	return contentsPrefix + delimeterA + innerContent + delimterB + contentsSuffix

if __name__ == '__main__':
    main()
