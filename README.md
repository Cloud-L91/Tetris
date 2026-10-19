# Tetris in C (Raylib) 🕹️

A simple, casual Tetris clone built in C using **Raylib** on Visual Studio.

## Controls ⌨️

* **Arrow Keys / WASD**: Move piece (Left, Right, Down)
* **Spacebar**: Rotate piece
* **Up Arrow / W**: Move upward (debug)

## Features ✨

* All 7 classic tetrominoes with original palette colors
* Frame-rate independent delta-time gravity
* Wall and stack collision detection
* Piece rotation with basic wall-kicking

## How to Run 🚀

1. Open `Tetris.sln` in Visual Studio.
2. Make sure **Raylib** is linked in your project settings.
3. Hit **F5** and play!

> **Note:** If the linker throws a `CloseWindow` collision error (`LNK2005`), add `/FORCE:MULTIPLE` to Linker -> Command Line -> Additional Options.