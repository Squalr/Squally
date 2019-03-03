How to add new strings:

Preliminary steps:
- Add the bookmarklet.js file to your chrome bookmarks.

Steps:
- Go to https://translatr.varunmalhotra.xyz/
- Use it to select all languages that Squally will use.
- Type the text you want to translate
- Copy the JSON output to clipboard
- Run 'python .\ConvertTranslatrString.py' and paste the JSON. It's OK if some of the characters can't be displayed in your terminal, you should still be able to copy them.
- Paste the output of the python script into a new string JSON file. This just needs to be in the 'Data' directory in a location that makes sense.
- Run 'python .\GenerateStringFiles.py' to re-generate all string classes
- cd to the main directory, and run 'python .\GenerateCMakeFiles.py' to pick up the new files

NOTE TO OSX/LINUX USERS:
- Some stupid Unix Kernel limitation makes it painful to paste text > 1024 characters in length. For whatever reason, this only inputs Python while trying to get input from std::in. As a workaround, base64 encode the Translatr JSON, and run python .\ConvertTranslatrString.py -b64 BASE_64_DATA_HERE'

To make changes to the bookmarket.js script:
- Make changes to bookmarklet.source.js
- Rebuild the new script here: https://mrcoles.com/bookmarklet/ (jquery must be enabled)
