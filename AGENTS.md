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


- Rotation anchor points seem off? Some animations appear fine in their default position, but as the animation progresses, the joints deteriorate and appear to rotate around the wrong points.
- Animations loop forever. Quite possibly animation priorities not being respected properly under the new system? One shot animations repeat forever. `SquallyOutOfCombatAttackBehavior.cpp` -> `EntityOutOfCombatAttackBehavior.cpp` for instance repeats forever. This is not a bug in the behavior, as the old animation system handles this fine.
  - In fact, this demonstrates both issues for Squally. The bones in Squally's arms are all misrotated during the attack animation, and the attack animation repeats forever.


## Important Information
Append important discoveries. Compact regularly.

Information found in initial audit:
- Legacy spriter2dx maps pivot to cocos as `anchor = (pivot_x, 1 - pivot_y)` (`external/spriter2dx/include/spriter2dx/ccimagefile.cpp`); new runtime previously used raw `pivot_y`.
- New runtime previously relied on `SmartAnimationNode` timer scheduling to emulate animation completion; completion now hooks directly to actual timeline wrap events in `SpriterAnimationNode::advanceTimelineTime`.
- Legacy spriter2dx maps Spriter position to cocos as `pos = (x, -y)` (`external/spriter2dx/include/spriter2dx/ccimagefile.cpp`); new runtime now applies the same sign flip when loading bone/object timeline positions.

## Agent Scratchpad and Notes
Append below and compact regularly to relevant recent notes, keep under ~20 lines.

- Patched pivot mapping in two places: sprite creation default anchor and timeline object anchor interpolation.
- Added loop-wrap completion callback plumbing in `SpriterAnimationNode` and switched `SmartAnimationNode` play-mode completion to that callback.
- Build command attempted, blocked by environment toolchain issue (`windows.h` missing), so runtime behavior still needs in-engine verification.
- Patched position mapping parity in timeline event mapping: bone/object positions now use `(x, -y)` to match spriter2dx.

### Concise Session Log
Append logs for each session here. Compact redundancy occasionally.
- Session: audited `SmartAnimationNode`, new Spriter timeline/events, and legacy spriter2dx parity points. Implemented pivot-Y parity fix and replaced timer-based one-shot completion with timeline wrap completion callback. Build attempt failed in this environment due missing Windows SDK headers (`windows.h`).
- Session: audited residual transform parity and found Y-position mismatch vs spriter2dx (`pos.y` sign). Patched new runtime timeline mapping to use `(x, -y)` for bones and sprites; runtime verification remains pending in-engine.
