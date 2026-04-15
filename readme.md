# Rock Paper Scissors — Arcade Edition

A console-based Rock Paper Scissors game with colored output, a navigable menu, and multi-round matches.

---

## Requirements

- C++17 or later
- CMake 3.10 or later
- Any compiler with `<thread>` and `<chrono>` support

## Compilation

### Using CMake (Cross-platform)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Or on Windows with Visual Studio:
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

### Direct compilation

**GCC/Clang:**
```bash
g++ -std=c++17 -o rock-paper-scissors main.cpp
```

**MSVC:**
```bash
cl /std:c++17 main.cpp
```

---

## How to Play

Run the executable from the terminal.

### Navigation
Enter the number corresponding to your choice in the menu.

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
CMakeLists.txt  — cross-platform build configuration
main.cpp        — full source code (single file)
readme.md       — this file
```