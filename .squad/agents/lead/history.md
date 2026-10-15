# Lead — History

## Project Context

**Extermination** — a small co-op game where the player defends land from dangerous vermin.

- **Language:** C++ (latest standard per `.github/copilot-instructions.md`)
- **Build:** hand-written `Makefile`; `make`, `make test` (build + run), `make check` (`cppcheck --enable=all`)
- **Dependencies:** SFML, Boost, CMake + Ninja for the vendored `mfGUI`
- **Engine:** `Yuna` git submodule — core, physics, math, world, utils, `mfGUI`
- **Other submodule:** `MapBuilder`
- **Source:** `src/` — ~5,900 LOC across 108 files
- **CI:** `.github/workflows/makefile.yml` builds on `master` and `dev`
- **Tests:** none exist yet
- **Requester:** Marek Fischer

## Learnings

<!-- Append entries below. Format: **Date:** YYYY-MM-DD — **Learning:** ... **Context:** ... -->
