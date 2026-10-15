---
name: ui-verification
description: Verify UI/HUD layout (mfGUI widgets, text bounds, overflow) by rendering the real widget to an offscreen sf::RenderWindow and measuring pixels, and capture the RUNNING game in-engine via sf::Texture::update(window) — also documents why every X11 screenshot tool and all XTest input synthesis fail on this rootless-Xwayland host, and how to drive the game with a temporary in-engine hook instead
domain: quality
confidence: high
source: next-wave button countdown overflow incident (2026-10-15); running-game capture + input-synthesis investigation (2026-10-15)
---

## Headline rule

**Re-implementing a widget's math in a model is not verification — it tests your model, not the widget.**

A harness that hand-replicated `mf::component::Text::FormatText()`'s wrap math and computed bounds
arithmetically reported "ALL INSIDE" for all 31 countdown values, while the real button rendered
`(28s)` outside/below the button. The model was wrong; the widget was right. Use the **real class**,
render it, and **measure pixels**.

## When to use

- A layout/overflow/centering claim needs proof (text fits, text is centered, nothing clips).
- You changed a widget's size, character size, font, or text content.
- You are tempted to "verify" by computing bounds by hand. Stop and use this instead.

## Two different problems — pick the right technique

These are **not** alternatives to each other; they answer different questions.

| Question | Technique | Section |
|---|---|---|
| "Does this widget's layout fit / overflow / center correctly?" | Offscreen `sf::RenderWindow` + `capture()`, render the **real widget** | [Offscreen widget harness](#offscreen-widget-harness-verifying-one-widgets-layout) |
| "What does the **running game** actually look like right now?" | In-engine `sf::Texture::update(window)` + `copyToImage()`, **before** `display()` | [Capturing the running game](#capturing-the-running-game-in-engine) |

Both are needed. The offscreen harness cannot show you the real HUD in its real state; the in-engine
capture cannot isolate a single widget's bounds.

## Why every X11 screenshot tool fails on this machine (root cause)

`DISPLAY=:0` is **rootless Xwayland**, not Xorg:

```
/usr/bin/Xwayland :0 -rootless -noreset -accessx -core -auth /run/user/1000/.mutter-Xwaylandauth.* ...
```

The X root window is **not a real framebuffer**. The game is an X11 client through Xwayland, but its
pixels live in the Wayland compositor's buffers, which no X11 client can read back. That single fact
explains every failure below — it is not a missing package or a bad flag.

### Method table (all observed on this host, 2026-10-15)

| Method | Result |
|---|---|
| `import -window root <file>` | `import: missing an image filename` — for **every** variant tried: with/without `-screen`, `-silent`, `--`, explicit `png:` prefix, absolute and relative paths, from a writable cwd |
| `import -window <id> <file>` | exit 0, but the image is grayscale with mean brightness **0.006** — effectively black |
| `ffmpeg -f x11grab` | fully black (mean **0**) at every size / offset / display tried |
| GNOME Shell D-Bus `org.gnome.Shell.Screenshot` | `AccessDenied: Screenshot is not allowed` |
| XDG Desktop Portal `org.freedesktop.portal.Screenshot` | **works**, but captures the **desktop only** — the game window's pixels are absent |
| **In-engine `sf::Texture::update(window)` + `copyToImage()`** | ✅ **WORKS** — see below |

Also not installed: `xwd`, `xvfb-run`, `scrot`. (`import` and `ffmpeg` *are* installed; they fail for
the root-cause reason above, not because they are missing.)

**Do not re-investigate this.** The root cause is understood and the working method is known.

## Capturing the running game (in-engine)

Add a temporary hook to the game's render loop. The **critical gotcha**:

> **Capture BEFORE `display()`.**
> `sf::RenderWindow::capture()` / `sf::Texture::update(window)` read the **back buffer**. After
> `display()` the back buffer is undefined (typically cleared), so you get a black or stale image.
> Capturing after `display()` was the first bug hit during this investigation.

Minimal correct ordering:

```cpp
// Inside the game's render path, immediately AFTER all draw calls and BEFORE display().
sf::Texture tex;
tex.create(mWindow->getSize().x, mWindow->getSize().y);
tex.update(*mWindow);                 // <-- reads the back buffer: must be pre-display()
sf::Image shot = tex.copyToImage();
shot.saveToFile(".scratch/frame.png"); // saveToFile returns bool — check it
mWindow->display();                    // <-- display() AFTER the capture
```

Notes:

- `sf::Texture::update(window)` is the non-deprecated form; `sf::RenderWindow::capture()` also works
  but is deprecated in this SFML version (the warning is expected and harmless).
- `sf::Image::saveToFile()` returns `bool` — check it, or you will silently write nothing.
- Create the `.scratch/` directory first; `saveToFile` does not create parent directories.
- This is a **temporary debug hook**. It must be reverted before you finish — see
  [Cleanup discipline](#cleanup-discipline-mandatory).

## Input synthesis is impossible on this host

A separate, equally important finding. **You cannot click buttons or send keystrokes to the game on
this machine.** Do not spend time trying.

- `xdotool` is **NOT installed**, and `dnf install xdotool` is **blocked** (no sudo).
- `libXtst` (`/usr/lib64/libXtst.so.6`) and `XTest.h` (`/usr/include/X11/extensions/XTest.h`) **ARE**
  installed, and a working XTest tool **can** be built against them.
- But at runtime: `XWarpPointer` **works** (the pointer visibly moves), while
  `XTestFakeMotionEvent`, `XTestFakeButtonEvent`, and `XTestFakeKeyEvent` are **silently dropped** —
  no error, no effect.
- **Decisive control test:** `xmessage` (a plain X11 client, not the game) was focused and sent
  clicks + `Return`. It **never responded**. So this is **not game-specific** — XTest input synthesis
  is broken **system-wide** under rootless Xwayland. The Wayland compositor owns the real input
  pipeline and does not forward synthetic XTest events to Xwayland clients.
- **Conclusion:** to drive the game, use a **temporary in-engine hook** instead (see the console
  section below for the natural place to put one).

Not tested: whether a Wayland-native input path (e.g. `ydotool` / `libei` / the compositor's own
remote-desktop portal) would work. It was not attempted.

## The in-game console (the natural place for a debug hook)

- `Tab` toggles the console — bound in `src/States/Game/InitGame.cpp:17`.
- `Game::Update()` only advances the world while the console is **closed**
  (`src/States/Game/Game.cpp:58-62`). So opening the console pauses the game.
- Registered commands (`src/States/Game/InitGame.cpp:25-30`): `exit`, `render_qtree <n>`,
  `render_pathnodes <0|1>`, `history [count]`, `stats`, `next_wave`.
  - `history [count]` — dumps the console command history to **`stdout`**, newest first. This is the
    one that matters for headless troubleshooting: `Console::AddString` writes only to the in-game
    text box and never echoes to `stdout`, so without this command anything printed in-game is
    invisible to a terminal. Backed by `Yuna::Core::Console::GetHistory()`.
  - `stats` — one-shot snapshot of FPS, frame time, entity/enemy counts, next-wave countdown, and
    player position/velocity, printed to `stdout`.
  - `next_wave` — immediately launches the next wave (debug/cheat command, always registered).
  - The internal `help`, `clear`, and `bind` commands are registered by Yuna itself
    (`Yuna/src/core/console/InternalConsoleCommands.cpp`) — do not re-add them.
- **There is no command to switch game state.** The next-wave button's callback is wired separately
  in `Game::Init()`. `next_wave` covers the wave case; forcing a *state* change still needs a
  temporary hook.
- Since input synthesis is impossible (above), the console **cannot be driven externally either** —
  but it is the natural place to add a **temporary** debug command if you need to drive the game
  (e.g. force a wave, force a state) for a capture.

### Driving the game from a hook — what does NOT work

Two dead ends that cost real time. Do not repeat them.

1. **Do not construct a second `Game` outside the game loop.** A harness that does
   `Game game(window); game.Init();` and then calls `Console::ProcessCommand(...)` will print
   `Game initialized` and then **hang**. `Game`'s constructor needs a live, *running*
   `sf::RenderWindow`; a window that was never opened (or a `GameApplication` subclass that never
   calls `Run()`) leaves it blocked. Symptom: **no window opens at all**, and the process sits until
   killed. The hook must live **inside the real game loop**, not beside it.
2. **`help` blocks when called from a hook.** `ProcessCommand("help")` was reached successfully from
   a harness and then hung — it renders through the in-game console UI, which needs a render pass.
   Prefer commands that only write to `stdout` (`history`, `stats`) when testing from a hook.

Also note: the game **auto-advances** Splash → Menu after 3s (`Splash::mSplashDuration`), but the
Menu then **waits for a click** on `Play` (`src/States/Menu/InitMenu.cpp`). Since input synthesis is
impossible, a plain `./Extermination` run will sit on the menu forever and `Game::Init()` will never
run — so `stdout` stays completely empty. An empty `stdout` from a plain run is **expected**, not a
build failure. Do not re-run the binary hoping for output; use a hook.

## Cleanup discipline (MANDATORY)

Bulk screenshots and debug hooks leave debris. **Always clean up after taking bulk screenshots.**

- A repo-root `.scratch/` is **NOT** in `.gitignore` — leftovers show up as untracked noise in
  `git status`. (Only `.squad/.scratch/` is ignored, via `.gitignore:42`.) Either put scratch output
  under `.squad/.scratch/`, or delete the directory when done.
- Temporary in-engine debug hooks **MUST** be reverted, and the revert **verified**:
  - `git diff <submodule>/` is empty (for submodule changes)
  - `grep` for the debug macro / hook finds nothing
- After cleanup, confirm with `git status` that **only intended changes remain**.
- Kill any game processes you started, using `kill <PID>` with a specific numeric PID
  (`pkill` / `killall` are blocked on this host).

## Offscreen widget harness (verifying one widget's layout)

Use this when the question is about a **single widget's** layout — text fits, text is centered,
nothing clips. It renders the real widget class offscreen and measures pixels.

### Harness template (copy-paste, adapt the marked parts)

Save as `harness.cpp` in the repo root and build with the command in the next section.

```cpp
// Offscreen UI verification harness — real mf::Button, real font, pixel measurement.
// Build from the repo root (paths below are relative to it).
#include "mfGUI.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdio>
#include <string>

int main()
{
    const unsigned int W = 400, H = 200;
    sf::RenderWindow rt(sf::VideoMode(W, H), "offscreen", sf::Style::None);

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/AlfaSlabOne-Regular.ttf"))
    {
        std::fprintf(stderr, "font load failed\n");
        return 1;
    }

    // Build the button exactly as HUD::InitNextWaveButton() does.
    mf::Button *btn = mf::Button::Create();
    btn->SetPosition(0, 0)
        ->SetSize(230, 50)
        ->SetTextFont(font)
        ->SetCharacterSize(20)
        ->SetText("Next wave")
        ->SetTextColor(sf::Color::White)
        ->SetBackground(sf::Color(40, 40, 40))
        ->SetPosition(50, 50)->SetPositionPercentage(true, true);

    int overflow = 0;
    for (int s = 0; s <= 30; ++s)
    {
        btn->SetText("Next wave (" + std::to_string(s) + "s)");

        // Same per-frame centering math as HUD::CenterNextWaveButtonText().
        sf::FloatRect tb = btn->GetTextBounds();
        sf::Vector2f bs = btn->GetSize();
        btn->SetTextPosition((bs.x - tb.width) / 2.f - tb.left,
                             (bs.y - tb.height) / 2.f - tb.top);

        rt.clear(sf::Color::Black);
        btn->Render(&rt);
        rt.display();

        sf::Image img = rt.capture();
        int minX = W, maxX = -1, minY = H, maxY = -1;
        for (unsigned int y = 0; y < H; ++y)
            for (unsigned int x = 0; x < W; ++x)
            {
                sf::Color c = img.getPixel(x, y);
                if (c.r > 200 && c.g > 200 && c.b > 200)
                {
                    if ((int)x < minX) minX = x;
                    if ((int)x > maxX) maxX = x;
                    if ((int)y < minY) minY = y;
                    if ((int)y > maxY) maxY = y;
                }
            }

        sf::Vector2f p = btn->GetPosition();
        sf::Vector2f sz = btn->GetSize();
        bool inside = (minX >= (int)p.x && maxX <= (int)(p.x + sz.x) &&
                       minY >= (int)p.y && maxY <= (int)(p.y + sz.y));
        if (!inside) ++overflow;
        std::printf("s=%2d text x=[%3d..%3d] y=[%3d..%3d] button x=[%3d..%3d] y=[%3d..%3d] %s\n",
                    s, minX, maxX, minY, maxY,
                    (int)p.x, (int)(p.x + sz.x), (int)p.y, (int)(p.y + sz.y),
                    inside ? "INSIDE" : "OVERFLOW");
    }
    std::printf("overflow: %d/31\n", overflow);
    delete btn;
    return overflow == 0 ? 0 : 2;
}
```

Adaptation points:

- **Widget under test** — swap `mf::Button` for the real widget class; keep the construction chain
  identical to the production `Init*()` method (same size, character size, font, text).
- **Sweep** — replace the `s = 0..30` loop with the real input range (all strings, all sizes, all
  states) that the widget can be given at runtime.
- **Per-frame math** — copy the production update/centering function verbatim, not a paraphrase.
- **Pixel predicate** — `r>200 && g>200 && b>200` finds white-ish text. Change the threshold or
  channel test if the text color differs; keep the background dark so it does not match.
- **Window size** — must be large enough to contain the widget plus margin, or the scan clips.

## Build and run

From the repo root:

```bash
g++ -std=c++17 -O0 harness.cpp -o harness \
  -I Yuna/mfGUI/include -I Yuna/includes \
  -L Yuna/mfGUI/lib -lMFGUId \
  -lsfml-graphics -lsfml-window -lsfml-system

DISPLAY=:0 ./harness
```

- `sf::RenderWindow::capture()` is deprecated in this SFML version — the warning is expected and
  harmless.
- A display **is** available at `:0`; the harness needs it even though it renders offscreen.
- Exit code is `0` when nothing overflowed, `2` when something did — usable as a gate.

## Observed result (baseline, 2026-10-15)

```
s= 0 text x=[ 85..244] ... INSIDE
...
s=20 text x=[ 78..251] y=[ 64.. 85] button x=[ 50..280] y=[ 50..100] INSIDE
...
overflow: 0/31
```

Text x=[78..251] sits inside button x=[50..280] for all 31 countdown values.

## mfGUI coordinate model (non-obvious, cost real time to work out)

- `mf::component::Text::Draw()` renders at `*mPos + mRelPos`, where `*mPos` is the **widget's**
  `mTransform.mPosition` and `mRelPos` is the text's own relative offset.
- So `Button::SetTextPosition(x, y)` sets an **OFFSET relative to the button's position**, NOT an
  absolute screen position.
- `Widget::SetPosition()` **overwrites** `mTransform.mPosition` (and `mRelativePosition`). With no
  parent, calling it repeatedly is idempotent — so the default RESIZE listener
  (`SetPosition(mRelativePosition)` then `SetSize(mRelativeSize)`) does **NOT** double-apply the text
  offset. This was suspected as a bug and **disproven by experiment** — do not re-investigate it.
- `Text::FormatText()` wraps when the string exceeds
  `maxCharPerLine = (size.x / characterSize) * 2`. This is why the original 210px button at default
  character size 30 wrapped `Next wave (28s)` onto two lines (string was 258px wide). Widening to
  230px + character size 20 fixed it.
- `Text::GetLocalBounds()` and `Button::GetTextBounds()` were **added** to the `Yuna/mfGUI` submodule
  during this work (they did not exist before). `GetTextBounds()` returns the text's local bounds
  *before* the widget position is applied, which is exactly what the centering math needs.

## Anti-patterns

- Hand-replicating `FormatText()` / wrap math and calling the arithmetic result "verified".
- Trying to screenshot the running game with an X11 tool (`import`, `ffmpeg x11grab`, …) on this
  host — see the root cause above. Use the in-engine capture instead.
- Trying to drive the game with `xdotool` / XTest — input synthesis is broken system-wide here.
- Capturing the running game **after** `display()` — the back buffer is undefined; you get black.
- Asserting on `GetTextBounds()` alone without rendering — bounds are a model of the glyphs; the
  rendered pixels are the ground truth.
- Reusing a stale harness after changing the widget's size, font, or character size.
- Leaving `.scratch/` output or a temporary debug hook behind — see Cleanup discipline.
