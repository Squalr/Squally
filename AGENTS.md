# Agentic Current Task (Readonly Section)
Our current task is to audit the code for logic errors, typos, or other silly mistakes.

### Architecture Plan
[Readonly line] Modify sparingly as new information is learned. Keep minimal and simple. The goal is to keep the architecture in mind and not drift into minefields. If over ~40 lines, compact to ~20 lines and remove anything tangential to the current task.

[Writable List]
- 

## Current Tasklist (ordered)
[Readonly line] (Remove as completed, add remaining concrete tasks.)

[Writable List]

- 

# Notes from Owner (Readonly Section)
[Writable List]
- For world switching (for example title screen launching Pong), should the canonical schema-level mechanism be only state-machine/global events, or should we also support a dedicated world-transition runtime command queue? ANSWER: I mean there are probably many ways this can happen right? Like a script call to change worlds is typical. Do what a platform like Roblox would do.
- Also, we should move all individual games into their own folders, rather than bloating `runtime_bootstrap.rs` with all of this shit, defeating single responsibility principal.

## Critical Questions and Blockers for Owner
[Readonly line] Append difficult decisions here that the owner can come back to for providing guidance. If stuck on a problem, try to infer from the `README.md` what the owner would have wanted, and make note of it here.

[Writable List]
- 

## Important Information
[Readonly line] Append important discoveries relevant to the task at hand. If over ~40 lines, compact to ~20 lines and remove anything tangential to the current task.

[Writable List]
- 

## Agent Scratchpad and Notes
[Readonly line] Append below and compact regularly to relevant recent notes.  If over ~30 lines, compact to ~15 lines.

[Writable List]
- 
