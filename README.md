# Clear Vehicle Paths

A tiny quality-of-life mod for Satisfactory 1.2+. The 1.2 update replaced the old recorded
vehicle paths with the new node/segment path system and auto-converts old paths on save load.
This mod gives you a one-shot chat command to get rid of those converted paths (or all paths)
map-wide, instead of dismantling them one by one.

## Usage

Open chat (`Enter`) and type:

| Command | Effect |
|---|---|
| `/clearvehiclepaths count` | Dry run — reports how many segments exist and how many are legacy. |
| `/clearvehiclepaths` (or `/clearvehiclepaths legacy`) | Dismantles only paths converted from pre-1.2 saves. Paths drawn with the new 1.2 tools are untouched. |
| `/clearvehiclepaths all` | Dismantles **every** vehicle path segment and standalone path node on the map. |
| `/cvp` | Short alias for all of the above. |

In multiplayer, any player can type the command and it executes on the server — that's
how SML chat commands work — so coordinate before clearing.

**Back up your save before the first run.** Vehicles that were following removed paths will
stop and need new paths recorded.

## How it works

Legacy paths converted by the game are permanently flagged (`mIsLegacyPath` on
`AFGVehiclePathSegment`). The command iterates all path segments, filters on that flag, and
dismantles them through the game's own `IFGDismantleInterface` — the same code path the
build gun uses — so path nodes clean themselves up, path networks rebuild, and vehicle route
tables are sanitized by the vehicle subsystem automatically.

## Building

Standard SML 3.12+ / Satisfactory 1.2 (UE 5.6 CSS) mod plugin. Package with Alpakit or:

```
RunUAT.bat PackagePlugin -ScriptsForProject=<path>/FactoryGame.uproject -DLCName=ClearVehiclePaths -build -platform=Win64 -nocompileeditor -installed
```
