# Changelog

All notable changes to Clear Vehicle Paths will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

> **Audience note:** This changelog is read by players, not developers. Entries should describe what the user experiences — what was broken, what it felt like, and what's better now. Class names, internal APIs, and implementation details belong in code comments or design docs, not here.

---

## [1.0.0] - 2026-06-11

> *Initial release: one chat command to clear vehicle paths map-wide on Satisfactory 1.2.*

### Added

- **`/clearvehiclepaths` chat command** — removes vehicle paths from the whole map in one go, instead of dismantling them piece by piece. Satisfactory 1.2 converts every pre-1.2 recorded truck route into the new path system on save load, and a big save can be left with thousands of path pieces and no vanilla way to bulk-remove them. Built for a player whose converted routes had nowhere else to go — offline save editors don't support the 1.2 save format yet.
  - `/clearvehiclepaths count` — dry run: reports how many path segments exist and how many came from a pre-1.2 save, without changing anything.
  - `/clearvehiclepaths` (or `legacy`) — removes only paths converted from a pre-1.2 save; paths drawn with the new 1.2 tools are untouched.
  - `/clearvehiclepaths all` — removes every vehicle path on the map, including new-style paths and standalone path nodes.
  - `/cvp` — short alias for all of the above.
  - Thanks to Doug "the plug" Eiffel for the request, the requirements, and verifying the fix.
- Removal goes through the game's own dismantle handling, so path networks rebuild cleanly, vehicles on removed paths stop safely (and need new paths recorded), and nothing is hand-edited in the save. The mod stores nothing in your save and can be uninstalled after use.
- In multiplayer, the command executes on the server no matter which player types it (that's how SML chat commands work) — there is no host-only restriction.
- **Packaged for dedicated servers** — the release includes server builds for Windows and Linux alongside the game client, covering most hosted-server providers. Install the same version on the server and on every client.
