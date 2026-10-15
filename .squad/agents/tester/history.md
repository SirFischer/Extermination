# Tester — History

## Project Context

**Extermination** — a small co-op game where the player defends land from dangerous vermin.

- **Language:** C++ (latest standard per `.github/copilot-instructions.md`)
- **Build:** `make`, `make test` (build + run the game), `make check` (`cppcheck --enable=all`), `make re`, `make fclean`
- **Dependencies:** SFML, Boost, CMake + Ninja for `Yuna/mfGUI`
- **CI:** `.github/workflows/makefile.yml` — builds on `master` and `dev`; runs no tests
- **Test state:** no test suite, no framework, no test target beyond `make test` (launches the game)
- **Source:** ~5,900 LOC across 108 files in `src/`
- **Requester:** Marek Fischer

## Learnings

<!-- Append entries below. Format: **Date:** YYYY-MM-DD — **Learning:** ... **Context:** ... -->
