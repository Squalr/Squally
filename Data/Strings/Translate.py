#!/usr/bin/env python3

import argparse
import base64
import json
import os
import re
import requests
import sys
import uuid
from os import listdir
from os import path
from os.path import isfile, dirname, join, splitext, abspath, realpath, basename, relpath

def main():
    key_var_name = 'TRANSLATOR_TEXT_SUBSCRIPTION_KEY'
    if not key_var_name in os.environ:
        raise Exception('Please set/export the environment variable: {}'.format(key_var_name))
        
    languages = [
        'ar',
        'bg',
        'cs',
        'da',
        'de',
        'el',
        'en',
        'es',
        'fi',
        'fr',
        'hu',
        'it',
        'ja',
        'ko',
        'nl',
        'no',
        'pl',
        'pt-pt',
        'pt-br',
        'ro',
        'ru',
        'sv',
        'th',
        'tr',
        'uk',
        'vi',
        'zh-CN',
        'zh-TW'
    ]
    
    subscription_key = os.environ[key_var_name]
    endpoint = 'https://api.cognitive.microsofttranslator.com'
    path = '/translate?api-version=3.0'
    headers = {
    'Ocp-Apim-Subscription-Key': subscription_key,
    'Content-type': 'application/json',
    'X-ClientTraceId': str(uuid.uuid4())
    }
    params = ''
    
    for next in languages:
        params += ('&to=' + next)
    
    constructed_url = endpoint + path + params
    
    parser = argparse.ArgumentParser()
    parser.add_argument("-b64", "--base64", help="A base64 encoded string containing the encoded translatr string json", default="")
    encodedJson = ""
    
    constructed_url = endpoint + path + params

    try:
        args = parser.parse_args()

        encodedJson = args.base64
    except:
        pass

    while(True):
        if (encodedJson):
            inputStr = str(base64.b64decode(encodedJson).decode('utf-8'))
            encodedJson = ""
        else:
            print("Type the text you wish to translate")
            inputStr = input()
            
            if (not inputStr):
                continue

            inputStr = inputStr.replace("&#39;", "'").replace("&#39;", "'").replace("&quot;", "'")

            body = [{
                'text': inputStr
            }]
        
            request = requests.post(constructed_url, headers=headers, json=body)
            response = json.dumps(request.json(), sort_keys=True, indent=4, ensure_ascii=False, separators=(',', ': '))
            translations = json.loads(response)[0]['translations']
		
            resultDict = {};
		
            for key in translations:
                language = key['to']
                translation = key['text']

                if (language == "zh-Hans"):
                    language = 'zh-CN'

                if (language == "zh-Hant"):
                    language = 'zh-TW'

                if (language == "pt"):
                    language = 'pt-BR'

                if (language == "pt-PT"):
                    language = 'pt'
                    
                resultDict[language] = translation

                if (language == "es"):
                    resultDict["es-419"] = translation
                    
            print(json.dumps(resultDict, indent=4, ensure_ascii=False))

if __name__ == '__main__':
    main()
