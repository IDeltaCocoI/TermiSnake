# TermiSnake

A classic Snake game written in strict C99 for the terminal, utilizing the ncurses library. The project features a modular architecture, clean memory management, and a reproducible development environment using Nix flakes.

## Controls

- **W, A, S, D** or **Arrow Keys** : Move the snake
- **Space** : Pause / Resume the game
- **Enter** : Restart the game (from the pause or game over screen)
- **Q** : Quit the game

## Dependencies

To build and run this game on a standard Linux system, you will need the following packages installed:
- A C99 compatible compiler (GCC or Clang)
- Make
- ncurses library (usually `libncurses-dev` on Debian/Ubuntu, or `ncurses-devel` on Fedora/Arch)

## Building and Running

### Standard Linux Environment

1. Navigate to the root of the project directory.
2. Compile the source code using Make:
   ```bash
   make
   ```
3. Launch the game:
   ```bash
   ./snake
   ```

### NixOS / Nix Users (Flake)

This project includes a `flake.nix` file, providing a fully isolated and reproducible development environment. If you have Nix installed with the `flakes` and `nix-command` features enabled, you do not need to install any dependencies manually.

1. Enter the development shell (this will automatically fetch GCC, Make, ncurses, and development tools like clangd):
   ```bash
   nix develop
   ```
2. Compile the game:
   ```bash
   make
   ```
3. Run the executable:
   ```bash
   ./snake
   ```

## Configuration

You can easily adjust the game settings without diving into the core logic. 
Open the `include/config.h` file to modify parameters such as:
- `INITIAL_LENGTH`: Starting size of the snake (default: 3)
- `GAME_SPEED`: Tick rate in microseconds (default: 100000)
- `SNAKE_BODY` & `APPLE_BODY`: Visual characters used in the terminal (default: `"  "` and `"()"`)

## Project Structure

```text
.
├── flake.nix
├── Makefile
├── include/
│   ├── config.h
│   ├── game.h
│   ├── movement.h
│   ├── point.h
│   └── snake.h
└── src/
    ├── game.c
    ├── main.c
    ├── movement.c
    ├── point.c
    └── snake.c
```
