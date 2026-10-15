# Squad Decisions

## Active Decisions

### 2026-10-15T15:17:29.363+02:00: Test harness scoping proposal

**By:** Lead
**What:** A concrete, phased proposal for adding a unit-test harness to Extermination — testable seams, framework pick, Makefile integration, CI integration, rollout, and risks. This is a SCOPING document only; nothing here is implemented.
**Why:** Marek requested a test-harness scope for a project with zero tests and CI that runs none.

---

#### 0. Executive summary

- **Framework pick: GoogleTest (gtest).** Already installed on this machine (v1.17.0, `pkg-config --exists gtest` succeeds), zero vendoring, and it links cleanly against a hand-rolled Makefile. Catch2 is not installed; Boost.Test is available but drags in a heavier build/link story for no benefit here.
- **The codebase is *mostly* untestable as-is.** The engine boundary (`Yuna`) and the game layer are tightly coupled to SFML resources, a live `Window`, and a running `Application` loop. There is **no dependency injection** for `ResourceManager`/`Window` in most classes — they are passed as raw pointers and dereferenced immediately in constructors.
- **However, there is a real, non-trivial set of pure-logic seams** that can be tested *today* with no refactoring: `Block`, `Wallet`, `Inventory` (partially), `Config`, `Actions`, `Map::Generate`/`ApplyPerlin`/`FitToGrid`/`GenerateGround` (with a null `ResourceManager`/`Window`), `Map::ApplyCollisionDetection`/`LockPlayerToMap`, `Entity` physics/controls, and the `Yuna` physics/math/pathfinding functions.
- **Biggest risk:** the `Yuna` submodule is a *separate repo*. Any test that links `Yuna/Yuna.a` couples the test suite to a submodule the team does not control in this repo, and `Yuna` has **no tests of its own** (`find Yuna -iname '*test*'` → empty). Testing `Yuna` internals from here is possible but fragile.

---

#### 1. Testable seams (the core of this task)

I read the actual code. Below, "testable" means: **can be instantiated and exercised without a window, GPU, audio device, or running game loop.** I cite file:line for every claim.

##### 1a. Testable TODAY, no refactoring required

These are pure data/logic units. They either have no SFML resource dependency, or their SFML dependency is a *value type* (`sf::Vector2f`, `sf::FloatRect`, `sf::Color`) that constructs fine headless.

| Unit | File | Why it's testable | Example assertions |
|---|---|---|---|
| `Block` | `src/States/Game/World/Map/Blocks/Block.hpp:24-67`, `Block.cpp:14-25` | Default ctor is empty (`Block.cpp:14-16`); all state is plain members with getters/setters. No texture is loaded in the ctor — `mTexturePath` is just a `std::string` (`Block.hpp:32`). | `SetPosition`/`GetPosition` round-trip; `IsSolid()` default `true` (`Block.hpp:29`); `IsBreakable()` default `false` (`Block.hpp:27`); `SetSize`/`GetSize`. |
| `Wallet` | `src/States/Game/Wallet/Wallet.hpp:3-15` | Header-only, `int coins = 20` (`Wallet.hpp:6`), `AddCoins` (`Wallet.hpp:14`). No SFML at all. | `GetCoins() == 20` on construction; `AddCoins(5)` → 25; `AddCoins(-100)` → negative (documents missing clamp — see §7). |
| `Config` | `src/States/Game/Config.hpp:14-18`, `Config.cpp:14-15` | Two static members, no dependencies. | Defaults `mRenderQTree == 0`, `mRenderPathNodes == false`. |
| `Actions` / `GetActionNames` | `src/Actions.hpp:17-32`, `Actions.cpp:14-29` | Free function returning a static `std::map`. No SFML. | Map is non-empty after first call; contains `"jump"`, `"move_right"`, etc.; idempotent across calls (the `if (!names.size())` guard at `Actions.cpp:17`). |
| `Inventory` (logic only) | `src/States/Game/World/Entities/Player/Inventory.hpp:22-43`, `Inventory.cpp:14-46` | Ctor only touches `sf::RectangleShape` (`Inventory.cpp:16-18`) — a value type, no GPU. `AddItem`/`NextItem`/`PreviousItem` are pure index math. | `NextItem` wraps to 0 (`Inventory.cpp:33`); `PreviousItem` wraps to `size()-1` (`Inventory.cpp:39`). **Note the bug in §7.** |
| `Entity` physics & controls | `src/States/Game/World/Entities/Entity.hpp:29-109`, `Entity.cpp:15-157` | Default ctor is empty (`Entity.cpp:15-18`). `HandlePhysics` (`Entity.cpp:30-43`), `WalkLeft/Right` (`Entity.cpp:130-142`), `Jump` (`Entity.cpp:144-157`), `TakeDamage(float)` (`Entity.cpp:88-91`), `ResolveCollision` (`Entity.cpp:104-124`) are all pure math on members. `GetGlobalBounds()` (`Entity.hpp:95`) is a pure computation. | Gravity applied when `!mOnGround` (`Entity.cpp:39-42`); `WalkRight` sets `mFacingLeft=false` (`Entity.cpp:140`); `TakeDamage(20)` reduces `mHealth`; `ResolveCollision` pushes apart overlapping rects (`Entity.cpp:108-122`). **Caveat:** `Entity::Update` (`Entity.cpp:46-58`) calls `mAnimations.Update()` and `mHealthBar.Update()` — those need checking (see §1c). |
| `Map` generation & collision | `src/States/Game/World/Map/Map.cpp:16-21`, `MapGenerator.cpp:17-147`, `CollisionDetection.cpp:15-62`, `PathGeneration.cpp:16-170` | `Map`'s ctor (`Map.cpp:16-21`) **only stores two raw pointers** — it does not dereference them. So `Map m(nullptr, nullptr)` constructs. `Generate` (`MapGenerator.cpp:122-147`) uses `srand`/`random` and `Block` values only. `ApplyCollisionDetection` (`CollisionDetection.cpp:15-52`) and `LockPlayerToMap` (`CollisionDetection.cpp:54-62`) operate on `Entity*` + `mBlockQTree`. | `Generate(20, 10, 3, 2, 42)` produces `mBlocks.size() >= 20`; `FitToGrid` snaps `y` to multiples of `mGridSize` (`MapGenerator.cpp:61`); `LockPlayerToMap` clamps `x` to `[100, (mLength-1)*mGridSize - width]` (`CollisionDetection.cpp:58-61`); `GetPath` returns empty when no nodes (`PathGeneration.cpp:105-107`). |
| `Yuna::Physics` | `Yuna/includes/physics/collisions/Collisions.hpp:21-25`, `Yuna/src/physics/collisions/Collisions.cpp` | Free functions on `sf::FloatRect`/`sf::Vector2f` values. No window. | `AABBCollision` overlapping vs. disjoint rects; `LineRectCollision`; `RayRectCollision` near-time; `DynamicRectCollision` contact normal. |
| `Yuna::Math` | `Yuna/includes/math/trigonometry/Trigonometry.hpp:23-24`, `Yuna/src/math/trigonometry/Trigonometry.cpp` | `Distance`/`Angle` on `sf::Vector2f`. Pure. | `Distance((0,0),(3,4)) == 5`; `Angle` quadrant correctness. |
| `Yuna::AI::createPath` | `Yuna/includes/ai/pathFinding/PathFinding.hpp:51`, `Yuna/src/ai/pathFinding/PathFinding.cpp` | A* over `PathNode` structs (`PathFinding.hpp:35-49`). Pure graph logic. | Path found between connected nodes; empty when disconnected; cost ordering. |
| `Yuna::Utils::QTree<T>` | `Yuna/includes/utils/qTree/QTree.hpp:42-66` | Header-only template. `Insert`/`Query`/`ForEach`/`DeleteAt` are pure spatial logic. `Render` (`QTree.hpp:63`) needs a window but is not required for logic tests. | Insert N items → `Query` returns them; `DeleteAt` removes; subdivision at `MAX_QUADTREE_NODES` (`QTree.hpp:21-23`). |

##### 1b. Testable ONLY with light refactoring (small, mechanical)

| Unit | Blocker | Refactor needed |
|---|---|---|
| `Statistics` | Ctor calls `InitFPSText()` etc. which call `mResourceManager->LoadFont(...)` (`Statistics.cpp:29,36,44`) — dereferences a `ResourceManager` that needs a real font file. | Split text-init out of the ctor, or inject a font-loading interface. Then `SetFrameTime` (`Statistics.cpp:73-80`) min/max tracking becomes testable. |
| `WaveManager` | `NextWave` (`WaveManager.cpp:33-51`) calls `mEntityManager->SpawnEnemy<T>()` (`WaveManager.cpp:47,49`), which calls `enemy->Init(mResourceManager)` (`EntityManager.hpp:61`) → loads textures. Also uses global `rand()` (`WaveManager.cpp:41`). | Extract the "buying power → spawn list" decision into a pure function returning a `std::vector<std::string>` of types; inject an RNG. Then the economy math (`mBuyingPower *= 1.2`, `WaveManager.cpp:36`) is testable. |
| `Weapon` | Ctor loads textures (`Weapon.cpp:18-20`); `Shoot` (`Weapon.cpp:29-41`) pushes to a **static** `ProjectileManager` (`Weapon.cpp:40`). | Inject `ResourceManager`; make `ProjectileManager` injectable or resettable. Then cooldown logic (`Weapon.cpp:31`) and velocity math (`Weapon.cpp:37-39`) are testable. |
| `Entity::Update` | Calls `mAnimations.Update()` (`Entity.cpp:53`) and `mHealthBar.Update(...)` (`Entity.cpp:57`). | Check whether `AnimationManager`/`HealthBar` ctors touch resources. If they do, inject or stub them. `HandlePhysics` alone is already testable (§1a). |
| `EntityManager` | Ctor stores pointers (`EntityManager.cpp:14-19`) — fine. But `Update` (`EntityManager.cpp:61-102`) calls `mMap->UpdateEntity`, `ProjectileManager::HandleCollisions` (static), and `mPickableManager->addPickable`. | Inject `Map`/`PickableManager` (already pointers) and make `ProjectileManager` non-static. Then entity lifecycle (spawn → death → pickable drop, `EntityManager.cpp:76-81`) is testable. |

##### 1c. NOT testable without significant refactoring

| Unit | Why | Refactor cost |
|---|---|---|
| `GameApplication` | Inherits `Yuna::Application` (`GameApplication.hpp:6`); ctor creates a window, sets VSync, inits console (`GameApplication.cpp:6-13`). | High — requires an `Application` abstraction. Not worth it for unit tests. |
| `Game`, `Menu`, `Options`, `Splash` states | All take `Yuna::Core::Window*` (`Game.hpp:52`, `Menu.hpp:34`, `Options.hpp`) and drive the state machine. | High. These are integration/e2e territory, not unit tests. |
| `World` | Ctor takes `ResourceManager*`, `Statistics*`, `Window*` (`World.hpp:64`); owns `Map`, `EntityManager`, `HUD`, `Fog`, `ParticleManager`. | High. Integration-level. |
| `HUD`, `Fog`, `Background`, `ParticleEffect`, `ParticleManager`, `ProjectileManager`, `PickableManager`, `HealthBar`, `Animation`, `AnimationManager` | All load textures/fonts or draw to a `Window` in ctor/`Render`. `ParticleManager`/`ProjectileManager` are **static singletons** (`ProjectileManager.hpp:44`, `ParticleManager.hpp:33`). | Medium–high. Singletons make isolation hard. |
| `Player` | Ctor takes `Inventory`; `Init` loads textures (`Player.hpp:42`); `Update` reads `EventHandler` (`Player.hpp:43`). | Medium. `EquipItem` (`Player.hpp:44`) could be extracted. |
| `Enemy`, `Dog`, `Base` | `Init` loads textures (`Enemy.hpp:43`, `Base.hpp:22`); `Enemy::Update` drives the AI state stack. | Medium. The **AI states themselves** (`ChaseState`, `AttackState`, `WildChaseState`) are closer to testable — see below. |
| AI states (`ChaseState`, `AttackState`, `WildChaseState`) | `Update(Entity*, std::stack<...>*, float)` (`ChaseState.cpp:10`) calls `pEntity->GetCurrentPath()`, `WalkRight/Left`, `Jump`, `Attack` — all `Entity` methods. `WildChaseState` uses `sf::Clock` (`WildChaseState.hpp:8-10`). | **Low–medium, and high value.** If `Entity` is testable (§1a), these become testable with a fake `Entity` subclass. `sf::Clock` in `WildChaseState` is the only real blocker — inject a clock or a time source. |

##### 1d. The `Yuna` boundary

`Yuna` is a **git submodule** (`.gitmodules:1-3`) built into `Yuna/Yuna.a` (`Yuna/Makefile`). It has **no tests** (`find Yuna -iname '*test*'` → empty). Its testable surface from this repo is the header-only `QTree` and the free functions in `Physics`/`Math`/`PathFinding` (§1a). Testing `Yuna` internals (Window, ResourceManager, Console, EventHandler) is out of scope — that belongs in the `Yuna` repo.

**Recommendation:** test `Yuna`'s pure functions *from here* only where the game depends on them (physics, math, pathfinding), and file a separate issue to add tests upstream in `Yuna`.

---

#### 2. Framework recommendation: GoogleTest

**Pick: GoogleTest (gtest).**

##### Evidence

- **gtest is already installed and pkg-config-able on this machine.** Verified: headers at `/usr/include/gtest/`, libs `/usr/lib64/libgtest.so` + `libgtest_main.so` (v1.17.0), and `pkg-config --exists gtest` succeeds with `-DGTEST_HAS_PTHREAD=1 -lgtest`. Zero vendoring, zero submodule, zero download.
- **Catch2 is NOT installed** (`ls /usr/include/catch2` → not found). Adopting it means either vendoring a single header (Catch2 v2) or adding a package dependency. Vendoring a header is cheap, but it adds a file the team must maintain and it is not what the machine already has.
- **Boost.Test headers exist** (`/usr/include/boost/test/`) and Boost is already a CI dependency (`libboost-container-dev`). But Boost.Test is the heaviest of the three: it needs `libboost-test-dev` (not currently installed — only `libboost-container-dev` is), it has a more complex link model (static vs. shared, `BOOST_TEST_DYN_LINK`), and its build-integration cost into a hand-rolled Makefile is the highest of the three.

##### Why gtest wins here specifically

1. **Build-integration cost is lowest.** gtest ships `libgtest_main.so`, which provides `main()`. That means a test binary needs *no* hand-written `main()` — which directly sidesteps the `main()` collision problem in §3.
2. **CI cost is one apt package.** `libgtest-dev` on Ubuntu (the CI runner is `ubuntu-latest`, `.github/workflows/makefile.yml:11`). On this Fedora machine it is already present.
3. **The project uses a hand-rolled Makefile, not CMake.** gtest's CMake integration (`find_package(GTest)`) is irrelevant here; what matters is that `pkg-config --cflags --libs gtest` gives a one-line compile/link recipe that drops straight into a Makefile rule. Catch2 would need the same treatment; Boost.Test would need more.
4. **Assertion ergonomics.** `EXPECT_*`/`ASSERT_*` with `<<` streaming is the most familiar to a C++ team and produces the clearest failure output for the numeric/physics assertions this codebase needs.

##### Rejected alternatives

- **Catch2** — not installed; would require vendoring or a new package. Its single-header convenience is real but does not outweigh "already installed and pkg-config-able."
- **Boost.Test** — Boost is already a dependency, but only `libboost-container-dev` is installed; Boost.Test needs `libboost-test-dev` and a more involved link setup. No benefit over gtest for this codebase.
- **doctest** — not installed; same vendoring cost as Catch2 with no offsetting advantage.
- **Hand-rolled assert macros** — zero dependency, but no test discovery, no filtering, no fixtures, no failure reporting. Not worth the maintenance for a suite that will grow.

---

#### 3. Build integration (hand-rolled Makefile)

##### The two concrete hazards

**Hazard A — source auto-discovery sweeps test files into the game binary.**
`Makefiles/default_vars.mk` does:
```make
SRCS += $(shell find $(SRCDIRS) -name '*.cpp')   # SRCDIRS := src
OBJS := $(patsubst src/%.cpp,obj/%.o,$(SRCS))
```
Verified: `find src -name '*.cpp'` currently returns **57** files. If tests are placed under `src/` (e.g. `src/tests/`), they are swept into `SRCS`, compiled into `obj/`, and linked into the `Extermination` binary — which then fails to link because of Hazard B.

**Hazard B — `main()` collision.**
`src/main.cpp:3` defines `int main()`. Any test file that also defines `main()` (or links `libgtest_main`) collides with it if both end up in the same link.

##### The fix: keep tests OUTSIDE `src/`, in a top-level `tests/` directory

Because `SRCDIRS := src` and the discovery is `find src ...`, a top-level `tests/` directory is **never** picked up by the game build. This is the single most important integration decision. Verified: `find src -name '*.cpp'` does not descend into a sibling `tests/`.

Proposed layout:
```
tests/
  unit/
    test_block.cpp
    test_wallet.cpp
    test_map_generation.cpp
    test_entity_physics.cpp
    test_yuna_physics.cpp
  Makefile            # or a Makefiles/tests.mk included by the root Makefile
```

##### Proposed Makefile additions (NOT implemented — proposal only)

Add a `test` target that **does not** disturb the existing `test` target's current meaning. **Important:** `make test` currently means "build and run the game" (`Makefile:test: all` → `./$(NAME)`). Renaming it would break the user's muscle memory and `.github/copilot-instructions.md` ("try to run the game after making changes (make test)"). So:

- **Keep `make test` as-is** (build + run the game).
- **Add `make unit`** (or `make test-unit`) for the unit suite. This avoids breaking the documented workflow.

Sketch:
```make
### --- unit tests (proposal only) ---
TEST_DIR    := tests/unit
TEST_SRCS   := $(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJS   := $(patsubst %.cpp,obj/tests/%.o,$(TEST_SRCS))
TEST_BIN    := unit_tests
GTEST_FLAGS := $(shell pkg-config --cflags --libs gtest gtest_main)

### Link against the game's objects EXCEPT main.o, plus Yuna.
GAME_OBJS_NO_MAIN := $(filter-out obj/main.o,$(OBJS))

.PHONY: unit
unit: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS) $(GAME_OBJS_NO_MAIN) Yuna.a
	$(CC) $(CFLAGS) $(TEST_OBJS) $(GAME_OBJS_NO_MAIN) $(LIBDEP) $(CLIBS) $(GTEST_FLAGS) -o $@

obj/tests/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_DIRS) $(INCLUDES) -c $< -o $@
```

Key points:
- `$(filter-out obj/main.o,$(OBJS))` removes the game's `main()` so `libgtest_main`'s `main()` is the only one. **This is the concrete answer to Hazard B.**
- `obj/tests/` is a new object subtree; `make clean` (`rm -rf obj`) already removes it.
- `pkg-config --cflags --libs gtest gtest_main` supplies both include paths and `-lgtest -lgtest_main`.
- The test binary links the *real* game objects, so tests exercise the actual compiled code, not a copy.

##### Alternative considered: separate `tests/Makefile`

A standalone `tests/Makefile` that recompiles the needed `src/` files is cleaner in isolation but duplicates the include-path logic and risks drift. **Recommendation: extend the root Makefile** (or `include Makefiles/tests.mk`) so include paths and flags stay single-sourced.

##### `make check` note

`make check` runs `cppcheck --enable=all $(INCLUDES) $(SRCS)` (`Makefile:check`). `cppcheck` is **NOT installed** on this machine (verified), and CI does not run it. This is a pre-existing gap, not part of this task — but if the test harness is added, `make check` should eventually also lint `tests/`. Flagged in §7.

---

#### 4. CI integration

Current workflow (`.github/workflows/makefile.yml`) runs on push/PR to `master` and `dev`, installs `build-essential cmake ninja-build libsfml-dev libboost-container-dev`, inits submodules, generates Ninja for `mfGUI`, and runs `make`. **It runs no tests.**

##### Required changes (proposal only)

1. **Add one apt package:** `libgtest-dev` to the `Install dependencies` step (`.github/workflows/makefile.yml:22`). On Ubuntu, `libgtest-dev` provides the headers and sources; `libgtest.so`/`libgtest_main.so` come from the same package on modern Ubuntu. (If the runner's `libgtest-dev` does not ship prebuilt `.so` files, the fallback is to build gtest from the shipped sources — but on `ubuntu-latest` this is not normally needed.)
2. **Add a test step after `make`:**
   ```yaml
   - name: unit tests
     run: make unit
   ```
   Placed after the existing `compilation` step so a build failure still fails fast.
3. **No change to the trigger branches** — tests should run on the same `master`/`dev` push/PR events.

##### CI cost

- One extra apt package (~small).
- One extra compile+link of the test binary. Given the game is ~5,900 LOC and the test suite starts small, this is seconds, not minutes.
- No new runner, no new service, no matrix.

##### Optional (later)

- Add `cppcheck` to CI (`sudo apt install cppcheck` + `make check`) — closes the pre-existing gap where `make check` exists but never runs. **Out of scope for this task**; noted in §7.

---

#### 5. Phased rollout

Realistic for a codebase with **zero tests** and heavy engine coupling. Each phase is independently shippable and leaves CI green.

##### Phase 0 — Harness skeleton (highest value, lowest friction)
**Goal:** prove the harness works end-to-end before writing meaningful tests.
- Create `tests/unit/` with **one** trivial test (e.g. `EXPECT_EQ(1 + 1, 2)`).
- Add the `make unit` target (§3) and the CI step (§4).
- **Exit criteria:** `make unit` passes locally; CI runs it on a PR.
- **Why first:** de-risks the build/CI integration in isolation. If the Makefile wiring is wrong, you find out on a trivial test, not on a physics test.

##### Phase 1 — Pure-logic units (no refactoring)
**Goal:** cover the seams in §1a that need zero code changes.
- `Block` (getters/setters/defaults).
- `Wallet` (arithmetic).
- `Config` (defaults).
- `Actions`/`GetActionNames` (map contents, idempotency).
- `Yuna::Math` (`Distance`, `Angle`).
- `Yuna::Physics` (`AABBCollision`, `LineRectCollision`, `RayRectCollision`, `DynamicRectCollision`).
- `Yuna::Utils::QTree` (insert/query/delete).
- `Yuna::AI::createPath` (A* correctness).
- **Why:** these are the highest-value, lowest-risk tests. They lock down the math the whole game depends on, and they need no refactoring.

##### Phase 2 — Game logic with light refactoring
**Goal:** cover `Map` generation/collision and `Entity` physics.
- `Map::Generate` / `ApplyPerlin` / `FitToGrid` / `GenerateGround` (construct `Map(nullptr, nullptr)` — verified safe, `Map.cpp:16-21`).
- `Map::ApplyCollisionDetection` / `LockPlayerToMap` (needs a `Map` with a populated `mBlockQTree`; `Generate` provides one).
- `Entity::HandlePhysics` / `WalkLeft` / `WalkRight` / `Jump` / `TakeDamage` / `ResolveCollision`.
- `Inventory` index math (and fix the `PreviousItem` bug — see §7).
- **Why:** this is the core gameplay logic. It is testable today with the `Map(nullptr, nullptr)` trick and a bare `Entity`.

##### Phase 3 — AI states (medium refactoring)
**Goal:** cover the enemy AI decision logic.
- Extract a time source from `WildChaseState`'s `sf::Clock` (`WildChaseState.hpp:8-10`).
- Test `ChaseState`/`AttackState`/`WildChaseState` `Update` against a fake `Entity` subclass that records `WalkLeft`/`WalkRight`/`Jump`/`Attack` calls.
- **Why:** AI is where subtle bugs hide (path popping, breakable-block damage). High value, but needs the clock injection.

##### Phase 4 — Economy & items (medium refactoring)
- Extract `WaveManager`'s spawn decision into a pure function + inject RNG (`WaveManager.cpp:33-51`).
- Make `ProjectileManager` non-static or resettable; test `Weapon::Shoot` cooldown/velocity (`Weapon.cpp:29-41`).
- Test `Statistics::SetFrameTime` min/max tracking (`Statistics.cpp:73-80`) after splitting font init out of the ctor.

##### Explicitly OUT of scope for unit tests
- `GameApplication`, `Game`, `Menu`, `Options`, `Splash`, `World`, `HUD`, `Fog`, `Background`, `ParticleManager`, `PickableManager`, `HealthBar`, `AnimationManager` — these are integration/e2e territory. If the team wants coverage here, that is a **separate** proposal for a headless integration harness (e.g. SFML with a null/offscreen render target), not unit tests.

---

#### 6. Risks and blockers

| # | Risk | Severity | Mitigation |
|---|---|---|---|
| 1 | **`Yuna` is a separate submodule with no tests.** Linking `Yuna/Yuna.a` couples the suite to a repo the team does not control here. | High | Test only `Yuna`'s pure functions from here; file an upstream issue to add tests in the `Yuna` repo. Do not attempt to test `Yuna` internals from Extermination. |
| 2 | **Static singletons** (`ProjectileManager`, `ParticleManager`) leak state between tests. | High | Make them resettable (add a `Clear()`/`Reset()`), or inject them. Until then, avoid tests that touch them. |
| 3 | **`ResourceManager`/`Window` are raw pointers dereferenced in ctors** (`Statistics.cpp:29`, `Weapon.cpp:18`, `Entity.cpp:26`). | High | Do not test those classes until DI is introduced. The §1a seams deliberately avoid them. |
| 4 | **`main()` collision** if tests land under `src/` or link the game's `main.o`. | Medium | Keep tests in top-level `tests/`; `$(filter-out obj/main.o,$(OBJS))` in the link rule (§3). |
| 5 | **`sf::Clock` in `WildChaseState`** makes AI timing non-deterministic. | Medium | Inject a time source before testing AI states (Phase 3). |
| 6 | **Global `rand()`/`srand()`** in `Map::Generate` (`MapGenerator.cpp:128`) and `WaveManager::NextWave` (`WaveManager.cpp:41`). | Medium | `Generate` takes a seed (`MapGenerator.cpp:122`), so it is reproducible — good. `WaveManager` uses unseeded `rand()`; inject an RNG. |
| 7 | **`-Werror`** (`default_vars.mk:CFLAGS`) means any warning in test code fails the build. | Low | Keep test code warning-clean; this is a feature, not a bug. |
| 8 | **`libgtest-dev` on the CI runner** may not ship prebuilt `.so` files on some Ubuntu versions. | Low | Fallback: build gtest from the shipped sources in CI. Verify on the first PR. |
| 9 | **Scope creep** — "while we're here, let's refactor everything for testability." | Medium | Enforce the phase gates. Refactoring is only justified when a phase needs it (§1b/§1c). |
| 10 | **`cppcheck` not installed** means `make check` cannot run locally or in CI. | Low | Pre-existing gap; out of scope. Noted in §7. |

##### Biggest risk (single sentence)
**The `Yuna` submodule boundary** — the game's most valuable logic (physics, pathfinding, quadtree) lives in a repo this project does not own and which has no tests, so the harness can only cover it from the outside, and any `Yuna` API change silently breaks the suite.

---

#### 7. Observations (NOT part of this task — reported, not fixed)

Per `.github/copilot-instructions.md`, code-quality feedback. These are **not** to be fixed as part of the test-harness work.

1. **`Inventory::PreviousItem` has an unsigned-underflow bug.** `mSelected` is `u_int8_t` (`Inventory.hpp:27`). `PreviousItem` does `mSelected--` (`Inventory.cpp:38`) then checks `if (mSelected >= mInventorySlots.size())` (`Inventory.cpp:39`). When `mSelected == 0`, `mSelected--` wraps to 255, and `255 >= size()` is true, so it sets `mSelected = size() - 1` — which happens to work *by accident*. But if the inventory is empty, `size() - 1` underflows to a huge value and `GetSelectedItem()` (`Inventory.hpp:35`) indexes out of bounds. **Real latent crash.**
2. **`Inventory::GetSelectedItem` has no bounds check** (`Inventory.hpp:35`) — `mInventorySlots[mSelected]` on an empty vector is UB.
3. **`Map::GenerateGround` reads `mBlocks[i + 1]` without bounds checking** (`MapGenerator.cpp:76`). The loop condition is `i < mBlocks.size()`, so at `i == size()-1` it reads one past the end. It relies on the `break` at line 77 firing first, which is fragile.
4. **`Map::GenerateGround` pushes to `mBlocks` while iterating it** (`MapGenerator.cpp:90` inside the loop at line 74). `mBlocks.push_back` can reallocate, invalidating the `mBlocks[i]` reference taken at line 76/84. This is a **use-after-reallocation** hazard.
5. **`Map::FitToGrid` also pushes to `mBlocks` while range-iterating it** (`MapGenerator.cpp:66` inside the range-for at line 58). Same reallocation hazard.
6. **`WaveManager::NextWave` can infinite-loop.** The `while (currentBuyingPower > 10)` loop (`WaveManager.cpp:39`) only decrements when a randomly-chosen enemy is affordable. If `rand()` keeps picking an unaffordable type, it spins. Also `mBuyingPower *= mBuyingPowerIncrease` assigns a `float` product to a `uint16_t` (`WaveManager.cpp:36`) — truncation, and it will overflow at high waves.
7. **`Entity::HandlePhysics` gravity is a no-op branch.** `(mVelocity.y < 0 ? 1 : 1.5f)` (`Entity.cpp:41`) — both branches apply gravity; the ternary only scales it. The comment says "stronger when falling" but the condition is on velocity sign, not falling state. Likely intended, but the `1` vs `1.5f` asymmetry is undocumented.
8. **`Entity::TakeDamage(float, ...)` uses `M_PI`** (`Entity.cpp:96`) without including `<cmath>` directly — it works only because SFML transitively includes it. Fragile.
9. **`Weapon::Shoot` uses raw `new`** (`Weapon.cpp:34`) and hands the pointer to a static `ProjectileManager` — ownership is unclear and there is no `delete` visible in this file. Potential leak.
10. **`Map::AddPathNode` has a self-deprecating comment** (`PathGeneration.cpp:128`: "I have absolutely zero shame for this...") on a `+ sf::Vector2f(0, -1)` fudge. The magic `-1` offset is unexplained and is exactly the kind of thing a test would pin down.
11. **`Config` is a global mutable struct** (`Config.hpp:14-18`) read from `Entity::Render` (`Entity.cpp:65`) and written from console commands (`ConsoleCommands.cpp:38,55`). Global state makes tests order-dependent.
12. **`make check` is dead** — `cppcheck` is not installed and CI never runs it (`Makefile:check`, `.github/workflows/makefile.yml`). The target exists but has never been exercised.
13. **`test.txt` (22 KB) sits in the repo root** and is not referenced by the build. Likely a stray artifact.
14. **`Makefiles/default_vars.mk` sets `NAME := sandbox`** (line ~19) while the root `Makefile` overrides `NAME := Extermination`. Confusing dead default.
15. **`GameApplication` ctor/dtor are empty-bodied with `/* args */` placeholders** (`GameApplication.hpp:9`, `GameApplication.cpp:6`) — leftover scaffolding comments throughout the codebase (`Block.cpp:14`, `Entity.cpp:15`, etc.).

---

#### Appendix: verification commands used

```bash
### Tooling
pkg-config --exists gtest && echo OK          # OK
ls /usr/lib64/libgtest*.so                     # v1.17.0 present
ls /usr/include/catch2                         # not found
which cppcheck                                 # not found

### Source discovery (proves tests/ must live outside src/)
find src -name '*.cpp' | wc -l                 # 57
grep -n "SRCS" Makefiles/default_vars.mk       # SRCS += $(shell find src -name '*.cpp')

### main() collision
grep -rn "int main" src/                       # src/main.cpp:3

### Yuna has no tests
find Yuna -iname '*test*' -not -path '*/.git/*'  # empty
```

---

### 2026-10-15T15:17:29.363+02:00: Real-time testing evaluation (Jev / Laya)

**By:** Lead
**What:** Evaluation of whether a local "Jev" or "Laya" instance could drive the game in real time, plus the underlying architectural question of whether this codebase can be tested live at all.
**Why:** Marek asked whether a local Jev or Laya instance could test the game in real time. Follow-up to `lead-test-harness-scoping.md`.

---

#### 1. Disambiguation

I searched the repository (all branches, all history, `.squad/`, `.copilot/`, `Tools/`, `Yuna/`) and the sibling workspace (`/home/mfischer/Marek/Work/DeepVertic/{Games,Tools,Apps,Libraries}`) for the strings `jev` and `laya`. **Zero hits for either term.** Neither is referenced anywhere in this project or in any sibling project. So I cannot resolve these from the codebase — I have to reason from the names alone, and I will be explicit about confidence.

##### "Laya" — moderate confidence: LayaAir (web/JS engine)

Most plausible referent: **LayaAir** (layabox.com), a Chinese HTML5/TypeScript/JavaScript game engine with an IDE. Confidence that this is what he means: **~60%**. The remaining ~40% is "Laya" as a person's name, a project name, or a mishearing.

**Direct answer: LayaAir is not applicable to this codebase.** LayaAir is a JavaScript/TypeScript runtime that executes in a browser or in its own native JS runtime. Extermination is native C++17 compiled by `g++` (`Makefiles/default_vars.mk`: `CFLAGS := -Wall -Werror -Wextra -std=c++17`) linking SFML (`CLIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio`). There is no JS layer, no WASM build target, and no scripting host. To use LayaAir you would have to **port the game to LayaAir**, which is a rewrite, not a test harness. I will not invent a "bridge" — there is no sensible one. If he wants LayaAir, the honest framing is "that is a different engine, and adopting it means rewriting the game."

##### "Jev" — unresolvable. I need Marek to tell me.

I cannot establish what "jev" refers to with any reasonable confidence, and I will not fabricate a tool. Candidates I considered and rejected as unsupported:

| Candidate | Why it is not a good fit |
|---|---|
| **JIT** (just-in-time compiler) | Not a testing tool; not something you "run a local instance of" to test a game. |
| **JVM** | Not applicable — this is native C++, not Java. |
| **GDB** | A real debugger, but nobody calls it "jev", and it is not a "real-time test" tool. |
| **Jevons** | No game-testing tool by that name that I can verify. |
| **A person named Jev** | Possible, but then "a local instance of Jev" makes no sense. |
| **A mishearing of "JVM"/"GDB"/"JIT"** | Plausible but unverifiable; guessing here would be worse than asking. |

**What I need from Marek:** the full name, a URL, or a one-line description of what Jev does. If it is a tool he has used before, the vendor/repo name is enough. Until then, any analysis of "Jev" would be fiction.

---

#### 2. Architectural reality check

This is the part that matters regardless of what Jev/Laya turn out to be.

##### 2.1 Is the game headless-capable today? **No.**

Not even close, and the blocker is structural rather than incidental.

- `Yuna::Core::Window` owns a **concrete `sf::RenderWindow` by value** — `Yuna/includes/core/Window.hpp:14`. It is not a `sf::RenderTarget*`, not an interface, not a template parameter. `Window::Create()` calls `mWindow.create(mode, title, style)` (`Yuna/src/core/Window.cpp:26-36`). There is no seam to substitute an offscreen `sf::RenderTexture`.
- `Yuna::Application` owns `Core::Window mWindow` **by value** (`Yuna/includes/Application.hpp:11`), and `Application::Run()` calls `mWindow.Create()` then `mStateManager.Run()` (`Yuna/src/Application.cpp:19-23`). So the window is created unconditionally on the path to any state.
- `mf::GUI` holds a **static `sf::RenderWindow *mWindow`** (`Yuna/mfGUI/src/mfGUI.hpp:16-17`), initialised from `Window`'s constructor via `GUI::Init(&mWindow)` (`Yuna/src/core/Window.cpp:6-9`). This is a second, independent hard coupling to a concrete window, and it is global state.
- `World::Update` calls `mWindow->SetView(...)`, `mWindow->GetViewMousePos()`, `mWindow->ResetView(true)` (`src/States/Game/World/World.cpp`). Gameplay logic is not separable from the window today.
- `Game::Render` calls `mWindow->Render(mPostEffectShader.get())` (`src/States/Game/Game.cpp:74-83`), and `Window::Render(sf::Shader*)` does an offscreen `mTexture.update(mWindow)` → `mSprite` → `mWindow.draw(mSprite, tShader)` round-trip (`Yuna/src/core/Window.cpp:70-79`). That round-trip is the *only* hint of a render-target seam in the codebase, and it still requires a real window to exist.
- `ResourceManager` loads from disk and **throws `std::runtime_error` on failure** (`Yuna/src/core/ResourceManager.cpp:24, 38, 52, 66, 84`). There is no null/headless mode and no asset-stub mode.
- `World`'s constructor loads `assets/shaders/global_lighting.frag` (`src/States/Game/World/World.cpp:242`) — **a file that does not exist in the repo** (`assets/shaders/` contains only `post-effects.frag`). So `World` construction currently depends on a missing asset. That is a live bug and also a headless blocker.

**Verdict:** headless rendering is not a configuration change here; it is a refactor.

##### 2.2 What a real-time/live harness would actually look like

Five realistic options for a native SFML game, and where this codebase stands on each:

**a) Scripted input injection.** The only injection seam that exists is `EventHandler::SetEventState(action, bool)`, which is public (`Yuna/includes/core/eventHandler/EventHandler.hpp:47`). `EventHandler` maps `sf::Keyboard::Key` / `sf::Mouse::Button` (+1000) / wheel (+2000) to `uint32_t` action IDs, and `Player::HandleEvents` reads them via `GetEventState((uint32_t)eAction::...)` (`src/States/Game/World/Entities/Player/Player.cpp:88-131`). So the *mechanism* is injection-friendly. The problem is reachability: `mEventHandler` is a **protected member of `State`** (`Yuna/includes/core/stateManager/State.hpp`), so nothing outside the state can drive it. There is also an existing scripted path — `Console::ProcessCommand(std::string)` and `Console::ProcessFile(path)` are public and static (`Yuna/includes/core/console/Console.hpp`), and `assets/scripts/DefaultBindings.cfg` / `UserBindings.cfg` already use a `bind <key> <action>` script syntax. But that path only issues *console commands*, not gameplay input. **Feasible with a small seam; not feasible today.**

**b) Deterministic replay.** Blocked on two fronts. Time is wall-clock everywhere: `State::Run()` uses a local `sf::Clock` (`Yuna/src/core/stateManager/State.cpp:31-56`), `Entity` holds `sf::Clock mFallClock, mPathRecalculationClock, mAttackClock` (`src/States/Game/World/Entities/Entity.hpp`), `Animation` uses `sf::Clock` (`Yuna/includes/.../Animation.hpp:26`), `WildChaseState` uses two more (`src/States/Game/World/Entities/Enemy/AIStates/WildChaseState.hpp:8-10`), and `Projectile` embeds an `sf::Clock mLifeClock` (`src/States/Game/World/Projectiles/Projectile.hpp`). There is no injectable time source. And RNG is unseeded: `World` calls `mMap.Generate(MAP_SIZE, 200, 3, 4, time(0))` (non-deterministic seed), `Enemy`'s constructor uses `random() % 100 < 30` to pick its initial AI state (`src/.../Enemy.cpp:20-24`), `Enemy::Init` uses `random() % 500 + 20000` (`Enemy.cpp:38-39`), `Enemy::TakeDamage` uses `random() % 100 < 50` for enrage (`Enemy.cpp:44-49`), and `WaveManager::NextWave` uses unseeded `rand()` (`src/.../WaveManager.cpp:33-51`). `Map::Generate` *is* seedable (`srand(pSeed)` at `src/.../MapGenerator.cpp:122-147`) — but the seed is `time(0)`. **Replay is impossible without injecting both clock and RNG.**

**c) Frame-stepping.** Blocked. `State::Run()` is a self-contained fixed-timestep loop: `while (mActive) { while (mElapsedTime >= mDeltaTime) { HandleEvents(); Update(); mElapsedTime -= mDeltaTime; } Render(); ... }` (`Yuna/src/core/stateManager/State.cpp:31-56`). There is no step hook, no max-frames parameter, no exit-after-N-frames, and no way to advance exactly one tick from outside. `StateManager::Run()` then loops `while (!mStateStack.empty()) { top()->Init(); top()->Run(); HandleStateAction(); }` (`Yuna/src/core/stateManager/StateManager.cpp:66-76`). **Frame-stepping requires extracting or instrumenting that loop.**

**d) Screenshot / visual diffing.** Possible *only* with a real window today, because rendering goes to `sf::RenderWindow`. `Window::Render(sf::Shader*)` already does an offscreen `mTexture.update(mWindow)` round-trip (`Yuna/src/core/Window.cpp:70-79`), which is the natural place to hang a capture hook — but it still needs the window. On a headless CI runner this fails outright. **Needs the render-target abstraction first.**

**e) Headless rendering.** Not possible today (see 2.1). The path is: abstract the render target so `sf::RenderTexture` can stand in for `sf::RenderWindow`, and de-static `mf::GUI`'s window pointer. SFML itself supports offscreen rendering fine; this codebase's ownership model is what prevents it.

##### 2.3 Minimum refactoring to make the game externally drivable

Concrete, ordered by dependency. Each item names the class that needs the seam.

1. **Render-target abstraction.** Introduce an interface (or template parameter) over the draw surface in `Yuna::Core::Window` (`Window.hpp:14`) so an `sf::RenderTexture` can substitute the `sf::RenderWindow`. This is the keystone — nothing else about headless works without it.
2. **De-static `mf::GUI`.** Replace the static `sf::RenderWindow *mWindow` (`Yuna/mfGUI/src/mfGUI.hpp:16-17`) with an injected target. Second keystone; `GUI::Init` is currently called from `Window`'s constructor (`Window.cpp:6-9`).
3. **Frame-step / scripted-exit hook in `State::Run()`.** Extract the fixed-timestep loop (`State.cpp:31-56`) so a harness can advance N ticks or run until a condition. Also give `StateManager::Run()` (`StateManager.cpp:66-76`) a bounded mode.
4. **Injectable time source.** Replace the `sf::Clock` members in `State`, `Entity`, `Animation`, `WildChaseState`, and `Projectile` with an injectable clock interface. This is the largest mechanical change by file count.
5. **Injectable RNG.** Replace global `rand()` / `random()` / `time(0)` with a seeded, injectable generator. Touch points: `World` (map seed), `Enemy` ctor/`Init`/`TakeDamage`, `WaveManager::NextWave`, `MapGenerator`.
6. **De-static the managers.** `ProjectileManager` is a static singleton (`src/.../ProjectileManager.hpp:26-31`: static `mResourceManager`, static `std::list<Projectile*> mProjectiles`, static `sf::Sprite mSprite`) and `ParticleManager` is a static singleton with a private constructor (`src/.../ParticleManager.hpp:26-33`). Neither has `Clear()`/`Reset()`, so state leaks across runs. Make them instance-owned by `World`, or at minimum add `Reset()`.
7. **Headless `ResourceManager` mode.** Either a null/stub mode or a "missing asset is non-fatal" mode, so a harness can construct `World` without a GPU context and without the missing `global_lighting.frag`.
8. **Input-injection seam.** Expose the `EventHandler` (currently protected in `State`) or add a scripted driver that calls `SetEventState`. The mechanism already exists (`EventHandler.hpp:47`); only reachability is missing.

Items 1–3 are the minimum for "drive the real game from outside." Items 4–5 are the minimum for "and get the same result twice." Items 6–8 are the minimum for "and do it repeatedly in one process."

##### 2.4 Is a web/JS engine applicable? **No.**

If "Laya" is LayaAir, the answer is a flat no. LayaAir targets JavaScript/TypeScript in a browser or its own JS runtime. This project is native C++17 + SFML with a hand-rolled Makefile and no scripting host. There is no bridge worth building, and I will not propose one. Adopting LayaAir means rewriting the game in a different language and engine — that is a product decision, not a testing decision.

---

#### 3. Comparison: real-time/live vs. the unit harness

| | Unit harness (prior scoping doc) | Real-time / live harness |
|---|---|---|
| **Cost to first value** | Low — GoogleTest already installed (v1.17.0), `tests/` + `make unit`, no source changes | High — requires refactor items 1–8 above before the first test runs |
| **Determinism** | Full — pure functions, fixed inputs | None today (wall-clock clocks, unseeded RNG) |
| **CI-friendly** | Yes — no GPU, no window, runs on `ubuntu-latest` | No — needs a display or the render-target refactor |
| **Speed** | Milliseconds | Seconds to minutes per scenario |
| **Catches** | Math (`Yuna::Math::Distance/Angle`), collision predicates (`Yuna::Physics::AABB/LineLine/LineRect/RayRect/DynamicRect`), A* pathfinding (`Yuna::AI::createPath`), map generation, inventory/economy arithmetic, AI decision logic, `Block` health thresholds | Integration wiring, state-machine transitions (`StateManager`), input→action→physics→render end-to-end, rendering/visual regressions, frame-rate and timing behaviour, resource-loading failures, singleton state leakage across frames |
| **Misses** | Anything requiring a live window, real timing, or cross-system wiring | Everything the unit tests cover, but slowly and flakily |

**What each catches that the other misses.** The unit harness catches logic errors cheaply and deterministically but cannot see whether the pieces are wired together — it would not have caught, for example, that `World` loads a shader that does not exist (`World.cpp:242` vs. `assets/shaders/`), because that is a construction-time integration failure. A live harness catches exactly that class of problem, plus visual regressions and timing bugs, but it cannot tell you *which* function is wrong, and today it cannot run reproducibly at all.

**Which first, and why.** Unit harness first, unambiguously. It is cheap, deterministic, CI-ready, and requires **zero** source changes — the prior scoping doc's Phase 0–2 can start immediately. The real-time harness requires refactoring the engine's ownership model (items 1–2), its time model (item 4), and its RNG (item 5) before a single test can run. Doing the refactor first would mean paying a large cost with no test coverage to protect the refactor itself — the worst possible ordering.

---

#### 4. Recommendation

**Decisive: build the unit harness first (Phases 0–2 from `lead-test-harness-scoping.md`), and treat real-time/live testing as a separate, later proposal that is gated on a deliberate engine refactor.**

Specifically:

1. **Do not pursue LayaAir.** It does not apply to a native C++/SFML codebase. If Marek wants LayaAir, that is a rewrite conversation, not a testing conversation.
2. **Do not pursue "Jev" until Marek says what it is.** I will not design around a tool I cannot identify.
3. **Proceed with the unit harness now.** It needs no source changes and delivers value this week.
4. **If Marek wants real-time testing, the honest path is:** (a) fix the missing `global_lighting.frag` reference, (b) do refactor items 1–3 to get external drivability, (c) add items 4–5 for determinism, (d) then build a scripted-input + screenshot-diff harness. That is a multi-week engine refactor, and it should be its own proposal with its own risk assessment — not folded into the unit-test work.
5. **A cheap intermediate exists and is worth noting:** `Console::ProcessCommand` / `ProcessFile` are already public and static, and the `.cfg` binding scripts already exist. A "smoke script" that boots the game and issues console commands is the lowest-cost live check available today, and it needs no refactor. It is not a test harness, but it is a real integration signal.

---

#### 5. Open questions for Marek

1. **What is "Jev"?** Full name, URL, or one-line description. This is the blocking question — I cannot evaluate it without knowing what it is. If it was a mishearing, what was the original word?
2. **Does "Laya" mean LayaAir (layabox)?** If yes, is he aware it is a JS/TS engine and that using it means rewriting the game? If no, what does it refer to?
3. **What does he actually want to observe?** Visual regressions? Gameplay balance? Crash reproduction? Frame-rate behaviour? The answer changes the design substantially — a crash-repro harness needs far less than a visual-diff harness.
4. **Is he willing to accept an engine refactor?** Items 1–5 above touch `Yuna` (a submodule, `https://github.com/SirFischer/Yuna.git`) as well as the game. That is a cross-repo change with its own review and release implications.
5. **Is there a display available on the target machine?** If the goal is "run it on my desktop and watch," that is a different (and much cheaper) proposition than "run it in CI."

---

**Confidence summary:** Laya ≈ LayaAir, ~60%, and not applicable either way. Jev = unknown, 0% — needs Marek. Headless-capable today = definitively no. Real-time testing viable = yes, but only after a substantial engine refactor. Unit harness first = high confidence.

---

#### CORRECTION — 2026-10-15T15:25:50.912+02:00

**The LayaAir guess in §1 above is WRONG. Do not act on it.**

Marek clarified: *"I meant the system 1 decision engine laya https://github.com/NandhaKishorM/laya"*.

**Laya is a Python ML decision engine, not a game engine.** It answers typed questions (`choice`, `score`, `noul`) over a text state in a single forward pass, with calibrated probabilities. Version 0.4.8, Python >= 3.10, `torch` + `transformers`. It ships an HTTP server (`laya-serve`) and an MCP stdio server (`laya-mcp-server`).

This changes the shape of the answer: LayaAir would have been "wrong engine, rewrite required"; Laya is "right kind of tool, wrong layer" — a text-in/decision-out model, and this game has no text and no decision seam.

**The corrected evaluation is in `lead-laya-evaluation.md`.** Headline: Laya cannot test this game in real time (no text, no telemetry, no injection or observation seam; its CPU latency is 20-35× over a 60 FPS frame budget). It has exactly one realistic role here — `laya-mcp-server` as **squad agent tooling** — and that is not game testing. The unit-harness-first recommendation in §4 above is unchanged.

**Jev remains unresolved.** One new lead: Laya's HTTP server exists specifically to speak "TypeSafe Jev's `/v1/systemone` wire protocol" (`laya/serve.py:1-8`), so Jev appears to be a related decision-API product. Hypothesis only — Marek should confirm.

---

### 2026-10-15T15:25:50.912+02:00: Laya decision-engine evaluation

**By:** Lead
**What:** Whether a local Laya instance can test Extermination in real time — corrected disambiguation, a direct answer, an honest survey of every candidate role (AI-behaviour classification, log triage, balance scoring, in-game decision engine, MCP agent tooling), the real-time latency budget, a ranked recommendation, and the questions still open.
**Why:** Marek clarified that "laya" means the System 1 decision engine at github.com/NandhaKishorM/laya, and asked whether a local instance could test the game in real time.

---

#### 1. Correction of the record

My earlier note (`lead-realtime-testing-evaluation.md`, §1) guessed **LayaAir** at ~60% confidence. **That guess was wrong.** Laya is not a game engine.

**Laya is a Python ML decision engine** — "Multilingual, non-autoregressive System 1 decision engine" (`/tmp/laya-probe/README.md:8`). It answers *typed questions* (`choice`, `score`, `noul`) over a text state in a single forward pass, with calibrated probabilities, and a router that picks a checkpoint per request. Version 0.4.8, Python >= 3.10, `torch` + `transformers` (`/tmp/laya-probe/pyproject.toml`). It ships an HTTP server (`laya-serve`), an MCP stdio server (`laya-mcp-server`), and language bindings for TS/.NET/Go/Java.

The correction matters because it changes the *shape* of the question. LayaAir would have been "wrong engine, rewrite required." Laya is "right kind of tool, wrong layer" — it is a text-in/decision-out model, and this game has no text and no decision seam.

---

#### 2. Direct answer: can Laya test this game in real time?

**No. Not in any sense of "test the game."**

Laya is a Python inference process that consumes a **text state** and returns **typed answers**. Extermination is a native C++17 binary (`Makefiles/default_vars.mk`: `CFLAGS := -Wall -Werror -Wextra -std=c++17`) linking SFML, with a hand-written Makefile and no scripting host, no IPC surface, and no text protocol.

Concretely, Laya cannot:

- **Drive the game.** There is no input path from Python into the game. The only injection seam is `EventHandler::SetEventState(action, bool)` (`Yuna/includes/core/eventHandler/EventHandler.hpp:47`), and `mEventHandler` is a **protected member of `Yuna::Core::State`** (`Yuna/includes/core/stateManager/State.hpp:20`) — unreachable from outside the state, let alone from another process.
- **Observe frames.** Rendering goes to a concrete `sf::RenderWindow` held **by value** in `Yuna::Core::Window` (`Yuna/includes/core/Window.hpp:14`). There is no render-target abstraction, no offscreen path, and no frame-capture hook. Nothing to feed Laya even if it could read images — and it cannot; it reads text.
- **Read game state.** There is no telemetry export, no log file, no structured trace. `Statistics` (`src/States/Game/Statistics.hpp`) holds FPS/frame-time/coins/player-transform and renders them **as `sf::Text` on screen** (`Statistics.cpp:60-72`) — it never writes them anywhere.
- **Run inside the game loop.** Laya is Python; the game is C++. Embedding it would mean an embedded interpreter plus a torch runtime inside a 60 FPS loop. That is not a testing decision, it is a rewrite of the product.

So the honest framing is: **Laya is not a test harness, and it is not a game-testing tool.** It does not drive, inject, or observe. Any role it has here is *adjacent* to the game, not *inside* it.

---

#### 3. Is there any legitimate role for Laya here?

I evaluated six candidates. I am not going to manufacture a use case, and I am not going to dismiss one reflexively. Two survive, and neither is "testing the game."

##### 3.1 AI-behaviour classification — **plausible in principle, blocked in practice**

**The idea.** The enemy AI is a hand-written state machine: `AIState::State { CHASE, WILD_CHASE, ATTACK, DEAD }` (`src/AI/AIState.hpp:8-14`), with `ChaseState`, `WildChaseState`, `AttackState` implementations. `Enemy::GetEnemyState()` exposes the current state (`src/States/Game/World/Entities/Enemy/Enemy.hpp:41`). One could imagine serialising behaviour traces to text and asking Laya "is this enemy stuck?", "is this wave balanced?".

**Why it is blocked.** Three independent blockers, any one of which is fatal today:

1. **There is no trace to classify.** Nothing in the codebase emits a behaviour trace. `Enemy::Update` (`Enemy.cpp:52-63`) mutates state and returns; `EntityManager::Update` (`EntityManager.cpp:60-100`) iterates entities and returns. No logging, no serialisation, no event stream. Producing traces is itself a feature to build.
2. **The AI is not deterministic, so traces are not reproducible.** `Enemy`'s constructor picks its initial state with unseeded `random() % 100 < 30` (`Enemy.cpp:20-24`); `Enemy::Init` positions with `random() % 500 + 20000` (`Enemy.cpp:38-39`); `Enemy::TakeDamage` enrages on unseeded `random() % 100 < 50` (`Enemy.cpp:44-49`); `WaveManager::NextWave` composes waves with unseeded `rand()` (`WaveManager.cpp:33-51`); `Map::Generate` is called with `time(0)` as the seed (`World.cpp:36`). Two runs of the same scenario diverge immediately. A classifier over non-reproducible traces cannot be validated.
3. **The classification is cheaper to do in C++ than to ask a model.** "Is this enemy stuck?" is a predicate over position history — a few lines of arithmetic. "Is this wave balanced?" is a predicate over wave composition and player health. Routing those through a 421M-parameter transformer over HTTP is strictly worse than a unit test, and it introduces a *probabilistic* answer where a *deterministic* one is available. That is a downgrade in test quality, not an upgrade.

**Verdict: not worth it.** The value Laya would add (natural-language criteria) is real but small, and the cost (build a trace format, make the sim deterministic, stand up a Python service, accept probabilistic answers) is large. If we ever want "is this enemy stuck?" as a test, it should be a C++ assertion in the unit harness, not a model call.

##### 3.2 Log / trace triage — **no input exists**

**The idea.** Classify test failures or crash logs into categories.

**Why it fails.** There are no logs. The project has **zero tests** (per `lead-test-harness-scoping.md`), so there are no test failures to triage. The game writes nothing to disk except via `Console::WriteBindingsToFile` (`Yuna/src/core/console/Console.cpp:145`), which writes key bindings. Crash output is whatever the OS prints. There is no corpus.

**Verdict: not applicable today.** If a unit harness lands and produces failure output, triage becomes *conceivable* — but at that point the failures are deterministic C++ assertions with stack traces, and a model adds nothing over reading them. Revisit only if the failure corpus becomes large and genuinely ambiguous, which is not the shape of this project.

##### 3.3 Balance evaluation — **the most defensible game-adjacent idea, still premature**

**The idea.** Score gameplay telemetry against criteria ("was wave 7 too hard?", "did the player have a viable strategy?").

**What it would actually require.** (a) A telemetry format — wave number, enemy composition, player health over time, base health, coins, time-to-clear. (b) A deterministic simulation to generate comparable runs (blocked, see 3.1). (c) A labelled corpus of "balanced" vs "unbalanced" waves to calibrate against — Laya's own docs are explicit that the shipped checkpoints are weak zero-shot on domain decisions: **0.362 accuracy** on their typed-decisions benchmark, rising to **0.766 only after fine-tuning on domain data** (`/tmp/laya-probe/README.md:89`). (d) A fine-tuning run (`laya-train`, `laya/train_cli.py`) on that corpus.

**Why it is premature.** Steps (a) and (b) are the same work as 3.1 and are not done. Step (c) requires a designer to label waves, which is the actual scarce resource. And the payoff is a *probabilistic* balance opinion, when the underlying question ("is wave 7 too hard?") is better answered by playing it or by a deterministic difficulty metric.

**Verdict: the only game-adjacent idea with a real (if distant) case — but it is a *game-design tool*, not a *test*, and it is gated on telemetry + determinism + a labelled corpus that do not exist.** Rank it below the unit harness and below the MCP option. Do not start it.

##### 3.4 Laya as the in-game decision engine — **out of scope, and a product decision**

**The idea.** Replace or augment the enemy AI with Laya.

**Flagged as a game feature, not testing.** This is explicitly out of scope per the task. I note it only to be clear that it is *technically* the most natural fit — Laya is literally a decision engine, and the enemy AI is literally a decision system — and that this is exactly why it is dangerous to conflate with testing. Adopting it would mean: an embedded Python/torch runtime or a sidecar process, a text serialisation of game state every decision, and a ~300 ms+ CPU round trip per decision (see §4). It would change the game's behaviour, its determinism, its performance profile, and its dependency surface. **Not a testing question. Do not pursue under this heading.**

##### 3.5 MCP integration — **the one realistic integration point, and it is agent tooling**

**The idea.** Laya ships an MCP stdio server (`laya-mcp-server` → `laya.mcp.server:main`, `pyproject.toml`). This project already has `.mcp.json` with a `squad_state` server. Add `laya` as a second MCP server so the squad agents can call typed decisions as tools.

**What it would actually require.** Exactly this, per Laya's own documented config (`/tmp/laya-probe/README.md:1375-1381`):

```json
{ "mcpServers": { "laya": { "command": "laya-mcp-server", "env": { "LAYA_DEVICE": "cpu" } } } }
```

Plus `pip install "laya[mcp]"` (pulls `mcp>=2.2.0`; the core package has no MCP dependency). Tools exposed: `laya_predict`, `laya_predict_batch`, `laya_route`, `laya_route_batch`, `laya_decide`, `laya_shortlist`, `laya_tournament`, `laya_preset`, `laya_status` (`README.md:1356`). Checkpoints download from Hugging Face on first use.

**What it would be good for.** Agent-side decisions that are genuinely ambiguous and text-shaped: triaging a batch of review comments, classifying a decision-inbox entry, routing a task to the right squad member, scoring a changelog entry's risk. These are real, and they are exactly the shape Laya is built for.

**What it would NOT be.** It would not test the game. It would not touch `src/`, the Makefile, or CI. It is **agent tooling**, and Marek asked about testing the game. I am flagging it clearly as a different question with a different answer.

**Cost.** Low to try (one `.mcp.json` entry, one pip install), but non-trivial in practice: a torch dependency on the dev machine, a multi-GB checkpoint download, and CPU latency of **~300 ms per question** on a laptop (`BENCHMARKS.md:263`: 329 ms p50 at 8 intra-op threads) rising to **~600 ms/question** on a 4-core server (`BENCHMARKS.md:361-371`). Every agent decision that routes through it pays that. And the honest caveat from Laya's own docs: the base checkpoints are **below the majority-class baseline** on their typed-decisions benchmark (0.362 vs 0.461, `BENCHMARKS.md:194`) — zero-shot quality on *our* domain is unproven and would need measuring before trusting it.

**Verdict: the only realistic integration point, and it is worth a *trial*, not an adoption.** It is agent tooling, not game testing.

##### 3.6 Summary table

| Candidate | What it needs | Worth it? |
|---|---|---|
| AI-behaviour classification | Trace format + deterministic sim + a Python service | **No** — cheaper and better as C++ assertions |
| Log/trace triage | A log corpus | **No** — no logs exist; deterministic failures need no model |
| Balance evaluation | Telemetry + determinism + labelled corpus + fine-tune | **Not yet** — real but distant; a design tool, not a test |
| In-game decision engine | Embedded runtime + per-decision round trip | **Out of scope** — product decision, not testing |
| MCP agent tooling | `.mcp.json` entry + `pip install laya[mcp]` | **Trial only** — realistic, but it is agent tooling |

---

#### 4. The real-time constraint

Marek said "in real time." Let me be concrete about what that would mean, because the numbers settle the question.

**The frame budget.** A 60 FPS game loop has **16.7 ms per frame**. `Yuna::Core::State::Run()` is a fixed-timestep loop with `mDeltaTime = 1.f / 60.f` (`Yuna/includes/core/stateManager/State.hpp:24`, `Yuna/src/core/stateManager/State.cpp:31-56`). Every millisecond spent on inference is a millisecond not spent on simulation and rendering.

**Laya's latency, measured, on CPU:**

| Hardware | Latency | Source |
|---|---|---|
| T4 GPU, 1 question | 33 ms | `README.md:8` |
| T4 GPU, batched | 7.2 ms/question | `README.md:132` |
| Laptop CPU (Ryzen 9 6900HX), 1 question, 8 threads | **329 ms p50** | `BENCHMARKS.md:263` |
| Laptop CPU, 3 questions over HTTP | **783 ms p50** | `BENCHMARKS.md:254` |
| Server CPU (EPYC, 4 cores), 1 question | **580 ms p50** | `BENCHMARKS.md:361-371` |
| Server CPU, 10 questions | **6,244 ms p50** | `BENCHMARKS.md:361-371` |

**Per-frame inference is not viable — by a factor of ~20 to ~35.** Even the *GPU* number (33 ms) is **2× over the 16.7 ms frame budget**, and the realistic local case is CPU at **329 ms — 20× over budget**. On a 4-core server it is 580 ms, **35× over budget**. There is no configuration in which Laya answers inside a frame.

**Per-event inference is also not viable.** An event (an enemy takes damage, a wave spawns) can fire many times per second. `Enemy::TakeDamage` (`Enemy.cpp:44-49`) fires on every hit; `ProjectileManager::HandleCollisions` (`ProjectileManager.cpp:44-58`) iterates every projectile against every entity every frame. At 329 ms per call, even one call per second would consume a third of the CPU budget and stall the loop.

**Per-wave inference is the only cadence that fits — and it still does not fit the game.** A wave is a discrete, infrequent event (`WaveManager::NextWave`, `WaveManager.cpp:33-51`). One call per wave at ~330 ms is *tolerable* if it happens off the render thread. But note what this concedes: **it is not real-time.** It is a post-hoc or between-wave analysis. And it still requires the telemetry and determinism that do not exist (§3.3).

**The honest conclusion on "real time":** Laya's latency budget and a 60 FPS game loop are incompatible by one to two orders of magnitude. Any use of Laya here is **offline, batched, or between-wave** — never per-frame, never per-event. If Marek's mental model was "Laya watches the game and reacts," that model does not survive the arithmetic.

---

#### 5. Recommendation

**Decisive: Laya is not a game-testing tool. It has exactly one realistic role here, and it is agent tooling, not testing.**

Ranked by value vs. cost:

1. **Do nothing with Laya for game testing. (Recommended.)** There is no role for it in testing this game. The blockers are structural — no text, no telemetry, no determinism, no injection seam, no observation seam — and the latency budget rules out anything real-time by 20-35×. Spending effort here would be effort not spent on the unit harness, which is cheap, deterministic, CI-ready, and needs **zero** source changes.

2. **Trial `laya-mcp-server` as squad agent tooling — separately, and only if Marek wants it.** This is the one place Laya genuinely fits: typed decisions over text, called by agents, for ambiguous agent-side questions (triage, routing, classification). Cost is low to try (one `.mcp.json` entry, `pip install "laya[mcp]"`), but it is **not** game testing, it adds a torch dependency and multi-GB checkpoints to the dev machine, and its zero-shot quality on our domain is unproven. **Propose only — I have not touched `.mcp.json`.** If Marek wants this, it should be its own decision with its own evaluation, and it should be measured on real squad decisions before adoption.

3. **Revisit balance evaluation only after telemetry and determinism exist.** This is the only game-adjacent idea with a real case, and it is gated on work that is not done: a telemetry format, a deterministic simulation, and a labelled wave corpus. It is a *game-design tool*, not a test. Do not start it now. If it is ever started, it should be justified by a designer's need, not by the availability of a model.

4. **Do not pursue AI-behaviour classification, log triage, or in-game decision-making.** The first two are better served by deterministic C++ assertions; the third is a product decision explicitly out of scope.

**And the standing recommendation from the prior note still holds, unchanged: build the unit harness first.** It is the cheapest path to real coverage, it needs no source changes, and it is the prerequisite for anything else — including any future telemetry work that a balance tool would need.

---

#### 6. What still needs clarifying

1. **"Jev" is still unresolved.** Marek clarified Laya only. I still do not know what Jev is, and I will not design around a tool I cannot identify. **What I need:** the full name, a URL, or a one-line description. If it was a mishearing, what was the original word?

   **One new lead worth noting:** Laya's own HTTP server exists specifically to speak **Jev's wire protocol** — `laya/serve.py`'s module docstring says it exposes "TypeSafe Jev's `/v1/systemone` wire protocol", that "Laya's `predict()` output is already schema-compatible with the Jev decision API", and that "a client written against Jev (for example the `hs-jev` Haskell client) can point its `baseUrl` at this server and keep working unchanged" (`/tmp/laya-probe/laya/serve.py:1-8`). Laya's README also references a `stuntd` project that "runs Laya locally behind the Jev API" (`README.md:1687`). So **Jev appears to be a related decision-API product** — plausibly the commercial/TypeSafe counterpart to Laya. That is a hypothesis, not a fact, and I am not treating it as resolved. **Marek should confirm whether "Jev" means this Jev.**

2. **What did Marek actually want to observe?** "Test the game in real time" could mean visual regressions, gameplay balance, crash reproduction, or frame-rate behaviour. The answer changes the design substantially — and none of the four is served by Laya. If he can say which one he cares about, I can point at the right tool.

3. **Was the MCP idea what he was reaching for?** If Marek's interest in Laya is really "give the squad better decision-making," that is a legitimate and cheap thing to trial — but it is a different question from the one he asked, and I want him to confirm which one he means before anyone touches `.mcp.json`.

---

**Confidence summary:** Laya is a Python ML decision engine, not a game engine — **certain** (verified in the clone). Laya cannot test this game in real time — **certain** (no text, no telemetry, no injection/observation seam; latency 20-35× over frame budget). No role for Laya in game testing — **high confidence**. MCP agent tooling is the one realistic integration point — **high confidence**, but it is agent tooling, not testing. Balance evaluation is the only game-adjacent idea with a real case, and it is premature — **high confidence**. Jev remains unknown — **0%**, needs Marek.

---

### 2026-10-15T15:33:38.872+02:00: Build hazard fixes for test-harness readiness

**By:** Engine
**What:** Fixed the two structural build hazards from Lead's test-harness scoping (`.squad/decisions/inbox/lead-test-harness-scoping.md` §3) so a unit-test harness *can* be added later. No test files, test targets, or dependencies were added; `make test` is unchanged.

**Hazard A — source auto-discovery sweeping test files into the game binary.**
`Makefiles/default_vars.mk` line 27 previously read `SRCS += $(shell find $(SRCDIRS) -name '*.cpp')`. Any `src/tests/` directory would have been swept into `SRCS`, compiled into `obj/`, and linked into `Extermination`, colliding with `src/main.cpp`'s `main()`. The `find` now excludes any `tests` directory:
```make
SRCS += $(shell find $(SRCDIRS) -name '*.cpp' -not -path '*/tests/*')
```
`-not -path '*/tests/*'` matches a `tests` path segment anywhere under `src/`, so `src/tests/`, `src/foo/tests/`, etc. are all excluded — safe by construction. A comment above the line documents the constraint and points unit tests at a top-level `tests/` directory (outside `$(SRCDIRS)`).

I rejected the `BLACK_LIST_SRCS` mechanism (line 23): it is consumed only by the `GEN_SOURCES` target (`Makefile:60-64`) to filter the generated `.srcs` file, and does **not** apply to `SRCS`/`OBJS`, so it cannot protect the real build.

**Hazard B — `main()` collision.**
`src/main.cpp:3` defines `int main()`, so a test binary linking the game's objects plus a test framework's `main()` (e.g. `libgtest_main`) would fail to link. `Makefiles/default_vars.mk` now defines a `main()`-free object seam immediately after `OBJS`:
```make
GAME_OBJS_NO_MAIN := $(filter-out obj/main.o,$(OBJS))
```
A future test target can link `$(GAME_OBJS_NO_MAIN)` alongside the framework's `main()`. The game build itself does not use this variable. A comment explains why it exists.

**Verification evidence:**
- `make` → exit 0; `./Extermination` produced (15,581,600 bytes, `ls -la Extermination`).
- `find src -name '*.cpp' | wc -l` → **57** (unchanged, before and after the change).
- Exclusion proof: temporarily created `src/tests/dummy.cpp`; raw `find src -name '*.cpp' | wc -l` returned 58 (57 + dummy), but the make-expanded `OBJS` contained **0** `dummy` entries — the dummy was not picked up by source discovery. `src/tests/` was then deleted and the count returned to 57.
- Hazard B proof: the make-expanded `GAME_OBJS_NO_MAIN` contains **56** `.o` entries and no `main.o` (57 − 1 = 56).
- `make test` → game launched ("Game initialized"); terminated by a 12 s `timeout` (exit 124) as expected for a windowed app that runs indefinitely. `make test`'s meaning is unchanged.

**Why:** Marek asked for the two build hazards from Lead's test-harness scoping to be fixed.

---

### 2026-10-15T15:33:38.872+02:00: Bug fixes from test-harness scoping

**By:** Gameplay
**What:** Fixed the eight bugs Lead found while scoping the unit-test harness (`.squad/decisions/inbox/lead-test-harness-scoping.md` §7). All fixes are in the gameplay domain. Build is green (`make`, exit 0, `-Wall -Werror -Wextra -std=c++17`, zero warnings) and the game launches (`./Extermination` → "Game initialized", ran until killed by timeout).

**B1 — `Inventory` unsigned underflow + missing bounds check** (`Inventory.cpp:30-46`, `Inventory.hpp:35`)
`mSelected` is `u_int8_t`. `PreviousItem` did `mSelected--` then `if (mSelected >= size()) mSelected = size() - 1`. For a non-empty inventory this wrapped correctly *by accident*; for an **empty** inventory `size() - 1` underflowed to a huge value and `GetSelectedItem()` indexed out of bounds (UB). `GetSelectedItem` had no bounds check at all.
**Fix:** `GetSelectedItem` returns `nullptr` when `mInventorySlots.empty()`. `NextItem`/`PreviousItem` return early (setting `mSelected = 0`) on an empty inventory; `PreviousItem` now uses an explicit `if (mSelected == 0) mSelected = size() - 1; else mSelected--;` instead of relying on unsigned wrap.
**Behavior:** Empty inventory — before: `GetSelectedItem()` read `mInventorySlots[255]` (UB, likely crash); after: returns `nullptr`, index stays 0. Non-empty — identical wrap-around (verified: 3 slots cycle 0→1→2→0 and 0→2→1→0; single slot stays 0). No observable gameplay change for a populated inventory.

**B2 — `Map::FitToGrid` push during range-for** (`MapGenerator.cpp:56-70`)
`mBlocks.push_back(Foliage(...))` inside `for (auto &block : mBlocks)` could reallocate and dangle `block`.
**Fix:** iterate `i < originalBlockCount` (snapshot) and index `mBlocks[i]`. RNG call order (`random() % 100`, `random() % 4`) is unchanged.
**Behavior:** Verified equivalent to the old loop for 500 seeds (the range-for's `end()` is cached by the compiler, so appended foliage was never visited; the only real defect was the dangling reference). Same foliage count and positions.

**B3 — `Map::GenerateGround` push while indexing** (`MapGenerator.cpp:72-93`)
Outer loop was `i < mBlocks.size()`, re-evaluated each iteration, so appended ground blocks were re-processed; `mBlocks[i]` references could be invalidated by reallocation.
**Fix:** I first tried snapshotting the size, then **proved by experiment that the growing size is load-bearing**: each surface block appends a column of ground below it, and those appended blocks are themselves processed, which is what fills the ground all the way down (5 surface blocks → 70 processed → 75 blocks). Snapshotting produced only one row per surface block and changed the map. The loop therefore keeps the re-evaluated `mBlocks.size()` bound, now with an explicit comment explaining why, and the `i + 1` access is bounds-checked (B4).
**Behavior:** Verified equivalent to the old loop for all realistic inputs (n ≥ 2 surface blocks, distinct-x, duplicate-x, and non-solid cases). The only divergence is n == 1, where the old code read `mBlocks[1]` past the end (pure UB); the new code safely breaks. `Generate` always creates `MAP_SIZE` (100) blocks, so this case is unreachable in the game.

**B4 — `Map::GenerateGround` out-of-bounds read** (`MapGenerator.cpp:76`)
`mBlocks[i + 1]` read one past the end at `i == size() - 1`, relying on the `break` firing first.
**Fix:** guard with `i + 1 < mBlocks.size()` in both the `break` condition and the `cornerBlock` computation. Termination semantics preserved.

**B5 — `WaveManager::NextWave` infinite loop + truncation** (`WaveManager.cpp:33-51`, `WaveManager.hpp:24`)
The `while (currentBuyingPower > 10)` loop only decremented when a randomly-chosen enemy was affordable; an unaffordable type in the dictionary would hang the game. `mBuyingPower *= mBuyingPowerIncrease` assigned a `float` product to a `uint16_t` — truncation and overflow at high waves.
**Fix:** build a list of affordable types each iteration, pick uniformly among them, and `break` when none are affordable. Clamp the growth: `mBuyingPower = (uint16_t)std::min((float)std::numeric_limits<uint16_t>::max(), mBuyingPower * mBuyingPowerIncrease)`.
**Termination argument:** every iteration either removes at least one affordable type from consideration by spending its price (strictly decreasing `currentBuyingPower`, which is bounded below by 0) or breaks. Since prices are ≥ 1, the loop runs at most `currentBuyingPower` times. Verified: 100 waves with the current dictionary, plus a dictionary containing a never-affordable 1000-price type, plus a dictionary with no affordable type at all — all terminate.
**Behavior:** spawn counts are **identical** to the old algorithm for the current dictionary (prices 10/15) across 200 seeds — the difficulty curve is unchanged. The clamp only affects waves ≥ 45, where the old code would have silently wrapped `uint16_t` (e.g. 65535 * 1.2 → 78642 → wraps to 13098, a difficulty *drop*); the new code holds at 65535. This is a deliberate fix of the overflow, not a curve change.

**B6 — Missing shader file** (`World.cpp:242`, `World.hpp:48,56`) — **needs judgment, see below**
`World::InitShader` loaded `assets/shaders/global_lighting.frag`, which does not exist and was never committed (`git log --all --diff-filter=D` is empty for it).
Investigation:
1. **Is it used?** No. `mGlobalLightingShader` is written only in `InitShader` and read nowhere. `InitShader` itself is **never called** — `World`'s ctor calls `InitBackgrounds`, `InitConsoleCommands`, `InitBase` (`World.cpp:112-114`) but not `InitShader`. It is dead code.
2. **What does `LoadShader` do on a missing file?** `Yuna/src/core/resourceManager/ResourceManager.cpp:49-58`: it constructs an `sf::Shader`, calls `loadFromFile(tPath, sf::Shader::Fragment)`, and on failure `throw std::runtime_error("Failed to load " + tPath)`. So had it ever been called, it would have **thrown and crashed the game** at world construction. Severity: latent crash, currently unreachable.
3. **Intent:** commit `1dcfa0c` ("added shaders to main game state to darken the scene") added both `post-effects.frag` (used by `Game::Render` via `mWindow->Render(mPostEffectShader.get())`, `Game.cpp:38,83`) and this dead `InitShader`. The scene darkening is already implemented by `post-effects.frag`; `global_lighting.frag` was an abandoned second attempt that was never wired up.
**Fix chosen: (a) remove the dead load.** I deleted `World::InitShader` and the `mGlobalLightingShader` member. This is the correct fix because the code is unreachable, unused, and would crash if reached; the intended darkening already exists via `post-effects.frag`. **I did not invent a shader.** If Marek actually wanted a separate global-lighting pass (e.g. a light map or day/night cycle), that is a new feature and needs his input — flagging it here rather than guessing.
**Behavior:** none — the code was dead. No observable change.

**B7 — `Weapon::Shoot` raw `new` leak** (`Weapon.cpp:34-40`, `ProjectileManager.hpp:30,38`, `ProjectileManager.cpp:15,27-42,59,72`)
`new Projectile` was handed to a static `ProjectileManager` whose `std::list<Projectile *>` removed pointers via `mProjectiles.remove(...)` without deleting them — a leak on every projectile that hit a block, hit an entity, or expired.
**Fix:** made ownership explicit. `mProjectiles` is now `std::list<std::unique_ptr<Projectile>>`, `AddProjectile` takes `std::unique_ptr<Projectile>` and `std::move`s it into the list, and `Weapon::Shoot` uses `std::make_unique<Projectile>()`. `remove()` now destroys the projectile. This is the correct-and-minimal fix: the narrower "delete before remove" alternative would have left ownership ambiguous and is easy to get wrong at the two `remove` sites (one of which is inside a range-for over the same list).
**Ownership model:** `ProjectileManager` exclusively owns every projectile from `AddProjectile` until removal; callers transfer ownership at the call site and must not retain the pointer. `Weapon::Shoot` no longer holds a raw pointer after the call.
**Behavior:** none observable — same projectiles, same positions, same collision handling.

**B8 — `M_PI` without `<cmath>`** (`Entity.cpp:96,98` and others)
`M_PI` and `std::cos`/`std::sin`/`std::atan2`/`std::abs`/`std::floor`/`std::pow` were used without a direct `<cmath>` include, working only because SFML transitively includes it.
**Fix:** added `#include <cmath>` to every file in the domain that uses these without a direct include: `Entity.cpp`, `Player.cpp`, `Weapon.cpp`, `ProjectileManager.cpp`, `World.cpp`, `HealthBar.cpp`, `CrateItem.cpp`, `GrateItem.cpp`, `CollisionDetection.cpp`, `Map.cpp`, `PathGeneration.cpp`. (`Camera.cpp` and `Pickable.cpp` already include `<math.h>`; `MapGenerator.cpp` already includes `<math.h>`.)
**Behavior:** none — include hygiene only.

**Verification**
- `make` → exit 0, zero warnings (the build uses `-Werror`, so a green build proves no new warnings). Full `make fclean && make` also clean.
- `./Extermination` → prints "Game initialized" and runs until killed by a 12 s timeout (exit 124); no crash, no exception. A display was available (`DISPLAY=:0`).
- B1: reasoned through the empty case and verified the index math in a standalone model (empty → `nullptr`, index 0; non-empty wrap-around unchanged).
- B2/B3/B4: verified old-vs-new equivalence in standalone models (500 seeds for `FitToGrid`; distinct-x, duplicate-x, and non-solid cases for `GenerateGround`).
- B5: verified termination for the current dictionary, an unaffordable-type dictionary, and a no-affordable-type dictionary; verified spawn counts identical to the old algorithm across 200 seeds; verified the `uint16_t` clamp.
- B6: read `Yuna/src/core/resourceManager/ResourceManager.cpp:49-58` and cited the `throw std::runtime_error` on load failure; confirmed `InitShader` has no call site and `mGlobalLightingShader` has no reader.

**Why:** Marek asked for the bugs found during test-harness scoping to be fixed.

**Open question for Marek (B6):** if a separate global-lighting pass was intended (light map / day-night cycle), it needs to be designed and wired up — the dead load was removed rather than guessed at.

---

### 2026-10-15T17:34:08+02:00: User directive — always clean up scratch artifacts

**By:** Marek Fischer (via Copilot)
**What:** Always clean up after taking bulk screenshots (or any other scratch/debug artifacts). Do not leave screenshot directories, temporary capture hooks, or scratch files behind in the working tree.
**Why:** User request — captured for team memory.

**Operational detail:** The `.scratch/` directory is **not** covered by `.gitignore`, so anything left there shows up as untracked noise in `git status`. Either clean it up at the end of the task, or add it to `.gitignore` — but the default expectation is cleanup, not ignore.

**Applies to:**
- Screenshot / video capture output
- Temporary in-engine debug hooks (must be reverted, and the revert verified)
- Any other scratch files created during investigation

**Verification expectation:** After cleanup, confirm with `git status` that the tree contains only intended changes, and state plainly what was removed.

## Governance

- All meaningful changes require team consensus
- Document architectural decisions here
- Keep history focused on work, decisions focused on direction
