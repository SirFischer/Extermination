# Changelog

## October 15, 2026
### Changed
- Build system: fixed two structural hazards that blocked adding a unit-test harness (see `.squad/decisions/inbox/lead-test-harness-scoping.md` §3).
  - **Source auto-discovery no longer sweeps test files into the game binary.** `Makefiles/default_vars.mk` now excludes any `tests` directory from the `find` that populates `SRCS` (`-not -path '*/tests/*'`). Previously a `src/tests/` directory would have been compiled into `obj/` and linked into `Extermination`, colliding with `src/main.cpp`'s `main()`. The exclusion makes this safe by construction; unit tests should still live in a top-level `tests/` directory outside `src/`.
  - **Added a `main()`-free object seam for future test binaries.** `Makefiles/default_vars.mk` defines `GAME_OBJS_NO_MAIN := $(filter-out obj/main.o,$(OBJS))` so a future test target can link the real game objects alongside a test framework's own `main()` (e.g. `libgtest_main`) without a duplicate-symbol collision. The game build itself does not use this variable.
  - No test files, test targets, or dependencies were added; `make test` is unchanged.

### Fixed
- Fixed eight bugs found while scoping the unit-test harness:
  - `Inventory::PreviousItem` unsigned underflow and missing bounds check in `GetSelectedItem` — an empty inventory could index out of bounds; `GetSelectedItem` now returns `nullptr` when there is no valid selection, and `NextItem`/`PreviousItem` handle the empty case explicitly. Wrap-around for non-empty inventories is unchanged.
  - `Map::FitToGrid` pushed foliage into `mBlocks` while range-iterating it, invalidating the loop reference on reallocation. Now iterates a snapshot of the original block count; generated foliage is identical.
  - `Map::GenerateGround` pushed ground blocks while indexing `mBlocks`, and read `mBlocks[i + 1]` one past the end on the final iteration. The growing-size iteration is now explicit and documented (it is load-bearing — it fills the ground downward), and the `i + 1` access is bounds-checked. Generated ground is identical.
  - `WaveManager::NextWave` could spin forever when `rand()` kept picking an unaffordable enemy type; it now picks only among affordable types and breaks when none are affordable. `mBuyingPower` growth is clamped to `uint16_t` max instead of silently overflowing. Wave composition is unchanged for the current enemy dictionary.
  - Removed a dead shader load: `World::InitShader` loaded `assets/shaders/global_lighting.frag`, which never existed and was never called or used. The scene darkening is handled by `post-effects.frag` in `Game`.
  - `Weapon::Shoot` leaked every projectile: raw `new` handed to `ProjectileManager`, which removed pointers from its list without deleting them. `ProjectileManager` now owns its projectiles via `std::list<std::unique_ptr<Projectile>>`.
  - Added direct `<cmath>` includes to files using `M_PI` and other math functions, which previously relied on SFML transitively including it.

## March 26, 2025
### Added
- Window resolution settings in Graphics Options menu
  - Added support for multiple resolution presets (1280x720, 1600x900, 1920x1080, 2560x1440)
  - Implemented proper scaling for all UI and game elements when changing resolutions
  - Resolution buttons use the existing UI styling for consistency