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

- [x] Run baseline validation build (`RelWithDebInfo`, target `all`) and record result before migration changes.
- [x] Generate a definitive inventory of files compiled by `cocos2d/cocos` and `cocos2d/external` targets (include CMake ownership and platform conditionals).
- [x] Create destination trees for migrated engine code: `Source/Engine/Core` (from `cocos2d/cocos`) and `Source/Engine/External` (from `cocos2d/external`), preserving relative include layout.
- [x] Port cocos CMake wiring into local engine CMake files, then switch root build from `add_subdirectory(cocos2d)` to local engine paths.
- [x] Remove cocos2d-specific setup/legacy files (including precompiled header artifacts) once replaced by local equivalents.
- [x] Replace git submodule-backed externals with `FetchContent` where needed and local source where required; remove submodule wiring from project configuration.
- [x] Re-run validation build and fix regressions until parity is restored.
- [x] Re-run validation build after flattening `Source/Engine/Core/cocos` into `Source/Engine/Core`, and fix any regressions.

## Important Information
Append important discoveries. Compact regularly.

- `CMakeLists.txt` now depends on `add_subdirectory(${PROJECT_SOURCE_DIR}/Source/Engine)` and `add_subdirectory(${PROJECT_SOURCE_DIR}/external)`.
- Submodule wiring has been removed from the repository configuration (`.gitmodules` deleted; no `160000` gitlink entries remain).
- `Source/CMakeLists.txt` directly configures target `cocos2d` compile features and links `cocos2d::cocos2d`; migration must keep this target contract or update all call sites.
- Migrated cocos source now lives directly under `Source/Engine/Core`; migrated cocos external sources are under `Source/Engine/External`.
- Baseline validation command succeeded on 2026-02-10: `"C:\Program Files\CMake\bin\cmake.EXE" --build c:/Projects/Squally/build --config RelWithDebInfo --target all --` returned `ninja: no work to do.`
- Build-derived Windows inventory generated at `cocos_migration_inventory_windows.txt` now includes ownership/condition annotations (`102` files from `cocos2d/cocos`, `8` files from `cocos2d/external`).
- `cocos2d/external/CMakeLists.txt` is empty; external source compilation is injected via `cocos2d/cocos/platform/CMakeLists.txt` (`../external/...` source entries).
- Validation build succeeded after migration/fixes on 2026-02-10 using MSVC developer environment bootstrap (`vcvarsall.bat x86`) before invoking the standard CMake build command.
- `external/CMakeLists.txt` now resolves `breakpad`, `spriterplusplus`, `spriter2dx` (and Apple-only `AFNetworking`) via `FetchContent` pinned to prior submodule SHAs.
- Legacy submodule working trees (`cocos2d`, `external/breakpad`, `external/AFNetworking`, `external/spriter2dx`, `external/spriterplusplus`) were removed from disk after wiring migration.
- Validation build succeeded on 2026-02-10 after submodule removal with VS2019 toolchain bootstrap: `vcvarsall.bat x86` then `"C:\Program Files\CMake\bin\cmake.EXE" --build c:/Projects/Squally/build --config RelWithDebInfo --target all --`.
- After flattening into `Source/Engine/Core`, cocos CMake relative external references were updated from `../../External/...` to `../External/...` where consumed by target source/include lists.
- Include directives in local `Source/` and `external/` code were normalized from `#include "cocos/...` to direct `#include "..."` paths to match flattened `Core` layout.
- `external/CMakeLists.txt` now applies a post-`FetchContent_Populate` include-prefix normalization for `spriter2dx` so fetched sources compile against flattened core headers.
- Validation build succeeded on 2026-02-10 after flattening with VS2019 toolchain bootstrap: `vcvarsall.bat x86` then `"C:\Program Files\CMake\bin\cmake.EXE" --build c:/Projects/Squally/build --config RelWithDebInfo --target all --`.

## Agent Scratchpad and Notes
(Append below and compact regularly to relevant recent notes, keep under ~20 trap parts).

- Path naming mismatch to resolve during migration planning: task text says `Squally/Engine/Core` and `Engine/External`, while current repo convention is under `Source/Engine/...`.

### Concise Session Log
Append logs for each session here. Compact redundancy.

- 2026-02-10: Audited current build wiring and submodule state. Added concrete migration task list and key constraints/discoveries.
- 2026-02-10: Ran baseline `RelWithDebInfo` validation build; successful (`ninja: no work to do`).
- 2026-02-10: Generated Windows compile inventory from `build/compile_commands.json` for `cocos2d/cocos` and `cocos2d/external` migration mapping.
- 2026-02-10: Migrated `cocos2d/cocos` into `Source/Engine/Core/cocos` and `cocos2d/external` into `Source/Engine/External`, switched root build wiring to local engine path, and updated cocos CMake relative external paths.
- 2026-02-10: Removed migrated cocos precompiled-header artifacts (`Source/Engine/Core/cocos/precheader.h`, `Source/Engine/Core/cocos/precheader.cpp`).
- 2026-02-10: Fixed include path regressions (`cocos/...`) by restoring cocos subtree layout and adjusting `spriter2dx` includes; full `RelWithDebInfo` build now succeeds.
- 2026-02-10: Replaced submodule-backed externals with `FetchContent`, removed `.gitmodules` and all gitlinks, deleted legacy submodule folders, and revalidated `RelWithDebInfo` build success (VS2019 `vcvarsall.bat x86`).
- 2026-02-10: Flattened `Source/Engine/Core/cocos` into `Source/Engine/Core` (removed extra wrapper directory) to match owner-requested layout.
- 2026-02-10: Updated flattened cocos CMake relative external paths and normalized `cocos/...` include prefixes (local source + fetched `spriter2dx` hook), then revalidated successful `RelWithDebInfo` build.
