# Agentic Current Task (Readonly)
Our current task is to move to the new Spriter Animation System that does not depend on a 3rd party library.

### Architecture Plan
Modify sparingly as new information is learned. Keep minimal and simple.
The goal is to keep the architecture in mind and not drift into minefields.

----------------------

Keep the old system behind the existing bool flag such that we can easily switch between to test for differences

Builds currently use the vscode cmake build UI, so any commands to attempt building should use whatever the equivalent is.

"C:\Program Files\CMake\bin\cmake.EXE" --build c:/Projects/Squally/build --config RelWithDebInfo --target all

This should be sufficient to compile. However, given that this is a video game, you are going to get nearly 0 information from compiling other than that it compiles. Focus more on auditing the existing spriterplusplus and spriter2dx code against our implementation. `SmartAnimationNode.cpp` is the abstraction point between the two systems.

## Current Tasklist (ordered)
(Remove as completed, add remaining concrete tasks. If no tasks exist, audit your work.)

- Reaper (`Resources/Private/Platformer/Entities/Enemies/CastleValgrind/Reaper/Animations.scml`) lower-body no longer inverts/folds during transitions after spin-aware rotation interpolation. Note form owner: Still mega busted.
  - The attempted fix in SpriterAnimationTimelineEventAnimation::computeDeltas() to respect spin still does not seem to work, even when coupled with the fix in SpriterAnimationTimelineEventAnimation.cpp.
- One-shot animations like attacks loop infinitely in the new system. Attempted fixes in SpriterAnimationTimelineEventAnimation.cpp have failed thus far.


## Important Information
Append important discoveries. Compact regularly.

Information found in initial audit:
- 

## Agent Scratchpad and Notes
Append below and compact regularly to relevant recent notes, keep under ~20 lines.

- 

### Concise Session Log
Append logs for each session here. Compact redundancy occasionally.
- 
