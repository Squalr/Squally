# Agentic Current Task (Readonly)
Our current task is to fix broken translations caused by a previous AI pass.

### Architecture Plan
Modify sparingly as new information is learned. Keep minimal and simple.
The goal is to keep the architecture in mind and not drift into minefields.

----------------------

## Blockers/Questions/Notes for Owner

- 2026-02-11: `Data/Strings/Platformer/Entities/Names/Helpers/VoidStar/Robot.json` has identifier/callsite name `Robot` while English source string is `Robbie`; I normalized other locales to `Robbie` (proper-name interpretation), but please confirm whether this helper should be treated as named companion (`Robbie`) or generic type label (`Robot`).
- 2026-02-11: `Data/Strings/Platformer/Entities/Names/Enemies/LambdaCrypts/SkeletalCleaver.json` English source term `Cleaver` is lexically ambiguous between role ("one who cleaves"/slasher) and weapon noun (meat cleaver); I localized with "slasher/cleaver-wielder" intent, but please confirm intended in-world naming nuance.
- 2026-02-11: Corrected English source typo in `Data/Strings/Platformer/Entities/EndianForest/Lycan/NobodyAllowedIntoTown.json` (`en` `Queens orders!` -> `Queen's orders!`) and normalized locale phrasings to match possessive "queen's orders" meaning.
- 2026-02-11: `Data/Strings/Platformer/Quests/EndianForest/FindElriel/Elriel/C_MeetMeInTown.json` has no `%s1` placeholder in English/source text (`I will head for the roof and beacon for a sky ship to take us home.`), but `Source/Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToElriel.cpp` injects `%s1` via `setStringReplacementVariables(Strings::Platformer_MapNames_EndianForest_Elbridge::create())`; please confirm whether the source line should include `%s1` (for town name) or if the replacement callsite is legacy/unused.
- 2026-02-10: `Source/Menus/Inventory/FilterMenu/HexusFilter.cpp` currently uses `Strings::Menus_Inventory_Equipment::create()` instead of `Strings::Menus_Inventory_Hexus::create()`, leaving `Data/Strings/Menus/Inventory/Hexus.json` without active non-generated callsites; please confirm whether this is intentional UI behavior or a binding bug.
- 2026-02-10: Data/Strings/Menus/Hacking/ClippyHelp/Items/SpeedRune/SpeedGainMul.json currently has no active callsites in Source (only generated Strings::* bindings) and still mirrors IncrementHealth inc/dec healing tutorial wording despite SpeedGainMul identifier; please confirm intended English/source behavior before full locale normalization.
- 2026-02-10: `Data/Strings/Menus/Hacking/Abilities/Debuffs/Enflame/RegisterEax.json` still contains several legacy locale phrasings that are semantically off from English source (`The amount of damage to deal.`), even after typo-token cleanup; please confirm whether to perform a full per-locale rewrite now or defer to dedicated linguistic pass.
- 2026-02-10: `Data/Strings/Menus/Hacking/Abilities/Buffs/SeekingBlade/SeekingBlade.json` had an English source mismatch (`en` duplicated `Scalding Blade` despite `SeekingBlade` identifiers/callsites); updated `en` to `Seeking Blade`, but non-English locales still mirror scalding wording and need owner guidance on whether to broad-normalize all locales now.
- 2026-02-10: `Source/Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/SerpentWandPlans.cpp` currently returns `Strings::Items_Equipment_Weapons_Wands_TaserRod::create()` in `SerpentWandPlans::getString()`; please confirm whether this is intentional or should be `SerpentWand`.
- 2026-02-10: `Data/Strings/Items/Misc/Keys/HellKey.json` currently duplicates `DemonKey` wording across locales while English source distinguishes `Hell Key` vs `Demon Key`; please confirm whether duplicated localization is intentional so we can safely normalize all locales.
- 2026-02-10: Corrected English source typo in `Data/Strings/Menus/Collectables/Animals/Tucan.json` (`en` `Tucan` -> `Toucan`) and left key/class identifiers unchanged (`Tucan`) since those are code/resource IDs.
- 2026-02-10: Corrected English source opcode typo in `Data/Strings/Menus/Hacking/Abilities/Abilities/BatSwarm/CommentHint.json` (`en` `jexcz` -> `jecxz`) to match the actual instruction shown/used in code.
- 2026-02-10: Corrected English source typo in `Data/Strings/Menus/Hacking/Abilities/Buffs/CallOfTheAncients/RegisterEdx.json` (`en` `recieve` -> `receive`).
- 2026-02-10: Corrected English/source opcode token typo in `Data/Strings/Menus/Hacking/Lexicon/Pages/ControlFlow/Jngle/Intro.json` (`en` `JNBL` -> `JNLE`) to match the intended signed-compare jump family.
- 2026-02-10: Corrected English/source copy-paste errors in `Data/Strings/Menus/Hacking/Lexicon/Pages/Data/{Pop/PointerHelp,Push/PointerHelp}.json` (`en` increment wording -> pop/push wording), but non-English locales still mirror the old increment semantics and need a full per-locale rewrite pass.
- 2026-02-10: `Data/Strings/Menus/Hacking/Abilities/Abilities/Waterball/ApplySpeed/*` currently has no active callsites (only generated `Strings::*` bindings found) and still uses legacy "fireball" wording in English/locales despite `Waterball` identifiers; please confirm whether this text should be normalized to "waterball" when/if these strings are reactivated.
- 2026-02-10: `Data/Strings/Menus/Hacking/Abilities/Debuffs/Manifest/CommentJumpReduce.json` had a confirmed English/source semantic mismatch (`Compare current damage to 0.` for a `jne reduceDamage` branch); updated `en` plus selected high-confidence locales, but several locales still mirror old compare phrasing and need a full per-locale rewrite pass.
- 2026-02-10: `Source/Objects/Platformer/Traps/FireBird/FireBird.cpp` currently binds `Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_RegisterXmm2::create()` for both `xmm2` and `xmm4`; `RegisterXmm4.json` exists but appears unused at runtime. Please confirm whether the second binding should use `RegisterXmm4`.
- 2026-02-10: `Data/Strings/Menus/Hacking/Objects/MayanDoor/{Combination1,Combination2,Combination3,RegisterEbx}.json` currently has no active callsites in `Source` (only generated `Strings::*` bindings found); please confirm whether these strings are intentionally inactive/legacy.
- 2026-02-10: `Source/Objects/Platformer/Traps/MetalSpikes/MetalSpikes.cpp` currently binds `Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_RegisterXmm2::create()` for both `xmm2` and `xmm4`; `RegisterXmm4.json` exists but appears unused at runtime. Please confirm whether the second binding should use `RegisterXmm4`.
- 2026-02-10: `Data/Strings/Menus/Hacking/Objects/PivotLauncher/SetTargetAngle/RegisterEax.json` currently uses pendulum-specific source wording (`The angle to which the pendulum will swing`) while under PivotLauncher identifiers, and `PivotLauncher/SetTargetAngle/*` has no active non-generated callsites in `Source`; please confirm whether this legacy set should be normalized (launcher-specific wording) or left unchanged until reactivation.

## Current Tasklist (ordered)
(Remove as completed, add remaining concrete tasks. If the list is empty, audit the codebase to come up with a plan for the next concrete steps.)

- 

## Important Information
- 