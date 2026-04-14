# Rock Paper Scissors — Arcade Edition

A console-based Rock Paper Scissors game for Windows with colored output, a navigable menu, and multi-round matches.

---

## Requirements

- Windows (uses Win32 API: `SetConsoleTextAttribute`, `GetAsyncKeyState`)
- C++17 or later
- Any compiler with `<thread>` support (e.g. MinGW-w64, MSVC)

## Compilation

**MinGW:**
```bash
g++ -std=c++17 -o rps.exe main.cpp
```

**MSVC:**
```bash
cl /std:c++17 main.cpp
```

---

## How to Play

Run `rps.exe` from the terminal or by double-clicking.

### Navigation
| Key | Action |
|-----|--------|
| ↑ / ↓ | Move menu cursor |
| Enter | Confirm selection |

### In-game
When prompted, type `1`, `2`, or `3` and press Enter to make your move.

| Input | Move |
|-------|------|
| `1` | Rock |
| `2` | Paper |
| `3` | Scissors |

---

## Rules

- Rock beats Scissors  
- Scissors beats Paper  
- Paper beats Rock  

Choose how many rounds to play. The player with the most round wins at the end takes the match.

---

## Project Structure

```
main.cpp   — full source code (single file)
readme.md  — this file
```