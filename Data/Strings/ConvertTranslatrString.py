from os import listdir
from os import path
from os.path import isfile, dirname, join, splitext, abspath, realpath, basename, relpath
import json
import os
import re
import sys

def main():
	while(True):
		print("Paste in the translation json from https://translatr.varunmalhotra.xyz/")
		inputStr = input().replace("&#39;", "'").replace("&#39;", "'").replace("&quot;", "'")
		
		translations = json.loads(inputStr)
		
		resultDict = {};
		
		for key in translations:
			resultDict[key['locale']] = key['string']
			
			if (key['locale'] == "es"):
				resultDict["es-419"] = key['string']
			
			if (key['locale'] == "pt"):
				resultDict["pt-BR"] = key['string']
		print()
		print(json.dumps(resultDict, indent=4, ensure_ascii=False))
		print()

if __name__ == '__main__':
    main()
