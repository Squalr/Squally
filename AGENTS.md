# Agentic Current Task (Readonly)
Our current task is to re-translate all strings in the game, as these were done with primitive tools that are frequently filled with translation errors.

The point is not to try and translate these out of context, nor use an API or script to translate. Instead, the goal is to build context such that the LLM agent knows how to translate each string in the game.

Builds can be validates with:
"C:\Program Files\CMake\bin\cmake.EXE" --build c:/Projects/Squally/build --config RelWithDebInfo --target all --

### Architecture Plan
Modify sparingly as new information is learned. Keep minimal and simple.
The goal is to keep the architecture in mind and not drift into minefields.

----------------------

- Systemically catalog all string json files in Data/Strings/*, and the progress on translating each.
    - We can use string_catalog.txt in the root project directory to track this.
- For each string, check its usage in the codebase. There are many strings that are not intended to be translated, such as those:
    - Strings that are using literal assembly instructions, or programming keywords.
- Placeholders like %s1, %s2, and so on must be kept in-tact. These are replaced with keywords using string replace operations.
    - Check the string replace callsites in C++ to ensure that the string being inserted is also correctly translated.
- Try to keep the tone across translations (ie the whimsical character name Guano, which kinda sounds like a name but very obviously isn't).
- If there is a problem or ambiguity that cannot be addressed, please include it in ## Blockers/Questions for Owner for the owner to take a look at later.

Some context:
- Cipher is a mini-game for connecting logical pins to unlock a cipher
- Hexus is a binary/hex/dec based card game that involves cards that apply assembly operations.
- This game has many hackable objects that involve inspecting objects at runtime to modify their assembly.

## Blockers/Questions for Owner

- 

## Current Tasklist (ordered)
(Remove as completed, add remaining concrete tasks. If the list is empty, audit the codebase to come up with a plan for the next concrete steps.)

- 

## Important Information
Append important discoveries. Compact regularly.

- 

## Agent Scratchpad and Notes
(Append below and compact regularly to relevant recent notes, keep under ~20 trap parts).

- 

### Concise Session Log
Append logs for each session here. Compact redundancy.

- 
