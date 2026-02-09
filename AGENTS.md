# Agentic Current Task (Readonly)
Our current task is to move to the new Spriter Animation System that does not depend on a 3rd party library.

### Architecture Plan
Modify sparingly as new information is learned. Keep minimal and simple.
The goal is to keep the architecture in mind and not drift into minefields.

----------------------

## Current Tasklist (ordered)
(Remove as completed, add remaining concrete tasks. If no tasks exist, audit your work.)

- Reconfirm baseline behavior with `UseNewAnimationSystem = true` and keep current Spriter runtime behavior unchanged (no transform/timeline architecture rewrite).
- Add `SmartAnimationNode` new-mode parity in the facade layer only: `setFlippedY`, `getFlippedX/Y`, `disableRender/enableRender`, and `AnimationPlayMode` (`ReturnToIdle`, `Repeat`, `PauseOnAnimationComplete`, `Callback`).
- Introduce a backend-neutral `AnimationPart` control target interface and refactor `AnimationPart` internals to consume it while preserving its public API.
- Implement a Spriter-backed `AnimationPart` adapter over `SpriterAnimationNode` parts (bone/sprite): timeline detach/reattach, transform overrides, alpha/visible overrides, sprite path override/readback, sprite size, tracked object behavior.
- Wire `SmartAnimationNode::getAnimationPart()`/`restoreAnimationPart()` to return functional `AnimationPart` in new mode and cache by part name as legacy path does.
- Keep Spriter changes additive and minimal (surface accessors/state only where required for parity); avoid altering existing reparenting/cascade/z-order logic unless a parity bug is proven by runtime verification.
- Add focused verification coverage for real callsites: launcher pivot (`pivot_bone`), bird beak detach/reattach (`beak_bone`), Squally equipment/eyes/mouth sprite swaps, projectile replacement, and weapon collision tracking on animated parts.
- After parity validation passes, remove dead legacy-only code paths and convert `UseNewAnimationSystem` from hardcoded local constant to a short-lived explicit toggle for validation, then default to new path.

## Important Information
Append important discoveries. Compact regularly.

Information found in initial audit:
- `UseNewAnimationSystem` is hardcoded `true` in `SmartAnimationNode.cpp`, so all current behavior depends on the new runtime path.
Information discovered during iteration:
- `SmartAnimationNode::playAnimation(...)` currently calls `spriterAnimation->playAnimation(...)`, but all play-mode logic immediately returns on `entity == nullptr`; callbacks/pause/return-to-idle/repeat semantics are bypassed in new mode.
- `SmartAnimationNode::getAnimationPart(...)` and `restoreAnimationPart(...)` are legacy-only (`EntityInstance`-based), so they return `nullptr`/no-op in new mode.
- `AnimationPart` gameplay usage depends on multiple behaviors (not just sprite swap): `replaceWithObject`, detach/reattach timeline, per-part rotation overrides (including Spriter-angle path), offsets, sprite size readback, tracked collision objects, opacity/visible overrides.
- `AnimationPlayMode` usage remains widespread (`Repeat` 40, `ReturnToIdle` 17, `Callback` 13, `PauseOnAnimationComplete` 9).
- New mode parity gaps in `SmartAnimationNode`: `setFlippedY`, `getFlippedX`, `getFlippedY`, `disableRender`, and `enableRender` still route only to legacy `AnimationNode`.
- `restoreAnimationPart(...)` has no gameplay callsites currently, but should still be preserved for API completeness.
- The local repo does not include raw `.scml` files, but generated resource tables reference a large number of `Animations.scml` assets across entities/objects, confirming heavy Spriter dependence.
- Existing Spriter runtime already runs with custom timeline/mainline cascade strategy; this should be treated as the stability baseline for this task (do not rewrite hierarchy/cascade model as part of parity work).

## Agent Scratchpad and Notes
Append below and compact regularly to relevant recent notes, keep under ~20 lines.

- Re-evaluation result: parity gaps are primarily facade/API bridging issues; full transform architecture rewrite is not required for initial production readiness.
- Keep the "existing spriter system untouched" constraint by making additive changes around it first (`SmartAnimationNode` + `AnimationPart` adapter layer).
- Validate against concrete callsites that currently rely on `AnimationPart` bones (`beak_bone`, `pivot_bone`) and sprite parts (`mainhand`, `offhand`, `eye_left/right`, `mouth`, trap parts).

### Concise Session Log
Append logs for each session here. Compact redundancy occasionally.
- 2026-02-09: Re-evaluated animation audit with `UseNewAnimationSystem` as baseline, confirmed parity blockers are in `SmartAnimationNode`/`AnimationPart` bridging, and updated plan to keep Spriter runtime behavior stable while restoring API parity.
