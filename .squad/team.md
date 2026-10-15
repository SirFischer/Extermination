# Squad Team

> Extermination

## Coordinator

| Name | Role | Notes |
|------|------|-------|
| Squad | Coordinator | Routes work, enforces handoffs and reviewer gates. |

## Members

| Name | Role | Charter | Status |
|------|------|---------|--------|
| Lead | Lead / Architect / Reviewer | .squad/agents/lead/charter.md | 🏗️ Active |
| Engine | Engine Developer | .squad/agents/engine/charter.md | 🔧 Active |
| Gameplay | Gameplay Developer | .squad/agents/gameplay/charter.md | 🎮 Active |
| Tester | Tester / QA | .squad/agents/tester/charter.md | 🧪 Active |
| Scribe | Decision Merger | .squad/agents/scribe/charter.md | 📋 Silent |
| Ralph | Work Monitor | .squad/agents/ralph/charter.md | 🔄 Monitor |
| Rai | RAI Reviewer | .squad/agents/Rai/charter.md | 🛡️ Background |
| Fact Checker | Fact Checker | .squad/agents/fact-checker/charter.md | 🔍 Verifier |


## Coding Agent

<!-- copilot-auto-assign: false -->

| Name | Role | Charter | Status |
|------|------|---------|--------|
| @copilot | Coding Agent | — | 🤖 Coding Agent |

### Capabilities

**🟢 Good fit — auto-route when enabled:**
- Bug fixes with clear reproduction steps
- Test coverage (adding missing tests, fixing flaky tests)
- Lint/format fixes and code style cleanup
- Dependency updates and version bumps
- Small isolated features with clear specs
- Boilerplate/scaffolding generation
- Documentation fixes and README updates

**🟡 Needs review — route to @copilot but flag for squad member PR review:**
- Medium features with clear specs and acceptance criteria
- Refactoring with existing test coverage
- API endpoint additions following established patterns
- Migration scripts with well-defined schemas

**🔴 Not suitable — route to squad member instead:**
- Architecture decisions and system design
- Multi-system integration requiring coordination
- Ambiguous requirements needing clarification
- Security-critical changes (auth, encryption, access control)
- Performance-critical paths requiring benchmarking
- Changes requiring cross-team discussion

## Project Context

- **Project:** Extermination
- **Created:** 2026-10-15
- **Owner:** Marek Fischer
- **What it is:** Small co-op game where the player defends land from dangerous vermin
- **Language:** C++ (latest standard)
- **Build:** `make` · `make test` (build + run) · `make check` (`cppcheck --enable=all`)
- **Dependencies:** SFML, Boost, CMake + Ninja (for `Yuna/mfGUI`)
- **Engine:** `Yuna` git submodule — core, physics, math, world, utils, `mfGUI`
- **Other submodule:** `MapBuilder`
- **Source:** `src/` — ~5,900 LOC across 108 files
- **CI:** `.github/workflows/makefile.yml` (builds on `master` and `dev`)
- **Tests:** none yet — `Tester` owns building the harness
- **Naming:** descriptive (universe: `descriptive`)
