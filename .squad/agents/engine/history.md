# Engine — History

## Project Context

**Extermination** — a small co-op game where the player defends land from dangerous vermin.

- **Language:** C++ (latest standard per `.github/copilot-instructions.md`)
- **Build:** `make`, `make test` (build + run), `make check` (`cppcheck --enable=all`), `make re`, `make fclean`
- **Dependencies:** SFML, Boost, CMake + Ninja for `Yuna/mfGUI`
- **Engine:** `Yuna` submodule — `includes/{ai,core,physics,utils,math,world}`, `src/{core,physics,utils}`, vendored `mfGUI`
- **Assets:** `assets/{fonts,images,maps,scripts,shaders,sounds,textures}`
- **CI:** `.github/workflows/makefile.yml` — deps, submodules, Ninja for `mfGUI`, then `make`
- **Recent work:** resolution presets (1280x720 → 2560x1440) with UI/game scaling; scene-darkening shaders; max-FPS slider
- **Requester:** Marek Fischer

## Learnings

<!-- Append entries below. Format: **Date:** YYYY-MM-DD — **Learning:** ... **Context:** ... -->
