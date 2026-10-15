# Gameplay — History

## Project Context

**Extermination** — a small co-op game where the player defends land from dangerous vermin.

- **Language:** C++ (latest standard per `.github/copilot-instructions.md`)
- **Build:** `make`, `make test` (build + run), `make check` (`cppcheck --enable=all`)
- **Engine:** `Yuna` submodule — core, physics, math, world, utils, `mfGUI`
- **Source layout:** `src/States/Game/World/Entities/` (Enemy, Player, Base, Animations), `src/States/Game/World/Items/`, `src/States/Game/HUD/`, `src/AI/`
- **Enemy AI states:** `ChaseState`, `WildChaseState`, `AttackState` under `Entities/Enemy/AIStates/`
- **Assets:** `assets/{maps,scripts,textures,sounds}`
- **Tests:** none exist yet
- **Requester:** Marek Fischer

## Learnings

<!-- Append entries below. Format: **Date:** YYYY-MM-DD — **Learning:** ... **Context:** ... -->
