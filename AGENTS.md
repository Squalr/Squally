# Agentic Current Task (Readonly)
Our current task is to move to the new Spriter Animation System that does not depend on a 3rd party library.

There is a `UseNewAnimationSystem` that toggles whether or not to use our system.

### Architecture Plan
Modify sparingly as new information is learned. Keep minimal and simple.
The goal is to keep the architecture in mind and not drift into minefields.

----------------------

## Current Tasklist (ordered)
[Readonly line] (Remove as completed, add remaining concrete tasks.)

[Writable List]
- Fix held items (ie staff on title screen) not appearing held in new system
- Fix new system endlessly looping
- Fix complex animations generally not working. Simpler ones are often fine, but complicated ones (ie the reaper enemy) generally fail quite badly. Possibly due to flip, spin direction, coordinate system mismatches, improper angle handling, or many other potential root causes. Investigate.

# Important Information
Information found in initial audit:
- `UseNewAnimationSystem` is hardcoded `true` in `SmartAnimationNode.cpp`, so all current behavior depends on the new runtime path.

Information discovered during iteration:
- 

## Agent Scratchpad and Notes
Append below and compact regularly to relevant recent notes, keep under ~20 lines.

- 

### Concise Session Log
Append logs for each session here. Compact redundancy occasionally.
- 