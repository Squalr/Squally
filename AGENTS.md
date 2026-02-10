# Agentic Current Task (Readonly)
Our current task is to remove all sub repos, eliminate unused cocos internals, and migrate cocos2d-x into Squally/Engine/Core/, without introducing any regressions or alterations in functionality. Files under cocos2d/cocos/ should end up under Squally/Engine/Core/. Files under cocos2d/external should end up under Engine/External.

Unused files can be deleted. Cocos2dx recompiled header can be deleted. Special cocos2dx related files can be deleted (ie setup files). The goal is to have the source, as needed, directly in our game. The only acceptable fetching allowed is through CMAKE FetchContent primitives.

### Architecture Plan
Modify sparingly as new information is learned. Keep minimal and simple.
The goal is to keep the architecture in mind and not drift into minefields.

----------------------

- 


Builds can be validates with:
"C:\Program Files\CMake\bin\cmake.EXE" --build c:/Projects/Squally/build --config RelWithDebInfo --target all --

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
