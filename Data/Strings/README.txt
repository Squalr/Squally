How to add new strings:

Preliminary steps:
- Add the bookmarklet.js file to your chrome bookmarks.

Steps:
- Go to https://translatr.varunmalhotra.xyz/
- Use it to select all languages that Squally will use.
- Type the text you want to translate
- Copy the JSON output to clipboard
- Run 'python .\ConvertTranslatrString.py' and paste the JSON. It's OK if some of the characters can't be displayed in your terminal, you should still be able to copy them.
- Paste the output of the python script into a new string JSON file
- Run 'python .\GenerateStringFiles.py' to re-generate all string classes
- cd to the main directory, and run 'python .\GenerateCMakeFiles.py' to pick up the new files

To make changes to the bookmarket.js script:
- Make changes to bookmarklet.source.js
- Rebuild the new script here: https://mrcoles.com/bookmarklet/ (jquery must be enabled)
