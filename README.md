# Sudoku Game Project

## Table of Contents

- [Sudoku Game Project](#sudoku-game-project)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Features](#features)
  - [Getting Started](#getting-started)
    - [Compilation](#compilation)
    - [Installation](#installation)

## Overview

This project is the final assignment for the programming laboratories at the Silesian University of Technology. It implements a Sudoku game in C++, providing a playable interface with features like a game menu and playability enhancements.

## Features

-   **Game Menu:** Introduces a menu for players to navigate and make choices.
-   **Playablbe Interface:** Game features graphical interface to enhance the overall playability of the Sudoku game.

## Getting Started

### Compilation

- Clone the repository:
```bash
git clone https://github.com/b14ucky/sudoku-final-project.git
```

- This game uses SFML library for graphical interface so you need to install it first. You can find the installation guide [here](https://www.sfml-dev.org/tutorials/2.6/).

- If you're using G++ compiler, you can compile the game using the following commands:
```bash
g++ -c *.cpp -IC:\dev\SFML-2.6.1\include -DSFML_STATIC

windres resource.rc -O coff -o resource.o

g++ *.o -o sudoku -LC:/dev/SFML-2.6.1/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

.\sudoku.exe
```

### Installation

- Go to **Releases**, select the latest release and download sudoku.zip.
- Extract .zip file and make sure that sudoku.exe and assets are the same directory.
- Enjoy the game.
