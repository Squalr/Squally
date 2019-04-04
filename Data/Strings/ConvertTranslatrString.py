#!/usr/bin/env python3

import argparse
from os import listdir
from os import path
from os.path import isfile, dirname, join, splitext, abspath, realpath, basename, relpath
import json
import os
import re
import sys
import base64

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("-b64", "--base64", help="A base64 encoded string containing the encoded translatr string json", default="")
	encodedJson = ""

	try:
		args = parser.parse_args()

		encodedJson = args.base64
	except:
		pass

	while(True):
		if (encodedJson):
			inputStr = str(base64.b64decode(encodedJson).decode('utf-8')
			)

			encodedJson = ""
		else:
			print("Paste in the translation json from https://translatr.varunmalhotra.xyz/")
			inputStr = input()

		inputStr = inputStr.replace("&#39;", "'").replace("&#39;", "'").replace("&quot;", "'")
		
		translations = json.loads(inputStr)
		
		resultDict = {};
		
		for key in translations:
			resultDict[key['locale']] = key['string']
			
			if (key['locale'] == "es"):
				resultDict["es-419"] = key['string']
			
			if (key['locale'] == "pt"):
				resultDict["pt-BR"] = key['string']
		print
		print(json.dumps(resultDict, indent=4, ensure_ascii=False))
		print

if __name__ == '__main__':
    main()
