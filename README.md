# *This project has been created as part of the 42 curriculum by zaleksan.*

# cub3D

## Description

cub3D is a simple 3D game engine developed as part of the 42 curriculum. The project is inspired by the classic game Wolfenstein 3D and introduces the fundamentals of computer graphics through the implementation of a raycasting engine.

The goal of the project is to render a pseudo-3D environment from a 2D map description, allowing the player to navigate through the world in real time. The engine calculates wall distances using raycasting techniques and projects the result onto the screen to create the illusion of depth.

Key features include:

* Parsing and validation of `.cub` configuration files
* Real-time raycasting rendering
* Player movement and rotation
* Wall texture mapping
* Floor and ceiling color rendering
* Collision detection
* Minimap visualization
* Event handling through keyboard input
* Efficient rendering using the MiniLibX graphics library

This project provided practical experience with:

* Computer graphics fundamentals
* Geometric calculations
* Parsing and data validation
* Event-driven programming
* Memory management in C
* Optimization techniques for real-time rendering

---

## Instructions

### Requirements

* Linux or macOS
* GCC compiler
* Make
* MiniLibX library
* X11 development libraries (Linux)

### Compilation

Clone the repository:

```bash
git clone <repository_url>
cd cub3D
```

Compile the project:

```bash
make
```

Additional Makefile rules:

```bash
make clean
make fclean
make re
```

### Execution

Run the program with a valid map file:

```bash
./cub3D maps/example.cub
```

### Controls

| Key | Action        |
| --- | ------------- |
| W   | Move forward  |
| S   | Move backward |
| A   | Strafe left   |
| D   | Strafe right  |
| ←   | Rotate left   |
| →   | Rotate right  |
| ESC | Exit game     |

---

## Technical Overview

### Parsing System

The parser reads and validates `.cub` configuration files, ensuring:

* Valid texture paths
* Correct floor and ceiling color definitions
* Proper map enclosure by walls
* Presence of a single player starting position
* Valid map characters

### Raycasting Engine

The rendering engine uses the Digital Differential Analyzer (DDA) algorithm to:

1. Cast rays from the player's position.
2. Detect wall intersections.
3. Calculate perpendicular wall distances.
4. Determine wall heights on screen.
5. Apply textures to rendered walls.

### Texture Mapping

Wall textures are loaded from XPM files and mapped onto rendered wall slices, providing a more realistic visual appearance.

### Collision Detection

The player cannot move through walls. Movement is validated against the map grid before updating the player's position.

---

## Learning Outcomes

Through this project, the following topics were explored:

* Raycasting algorithms
* DDA line traversal
* Texture mapping
* Coordinate systems
* Trigonometry in graphics
* Event handling
* Memory management
* Real-time rendering principles
* Basic game engine architecture

---

## Resources

### Documentation

* MiniLibX Documentation
* X11 Documentation
* GCC Documentation
* Make Documentation

### Books

* Computer Graphics: Principles and Practice — John F. Hughes, Andries van Dam, Morgan McGuire
* Fundamentals of Computer Graphics — Peter Shirley, Steve Marschner
* Ray Tracing from the Ground Up — Kevin Suffern

### Tutorials and Articles

* Lode Vandevenne's Raycasting Tutorial:
  https://lodev.org/cgtutor/raycasting.html

* Permadi's Ray Casting Tutorial:
  https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/

* Learn OpenGL:
  https://learnopengl.com/

### AI Usage

Artificial Intelligence tools were used as learning assistants during the development of this project.

AI assistance included:

* Understanding raycasting concepts and mathematical formulas
* Reviewing code structure and architecture decisions
* Explaining graphics-related algorithms
* Assisting with debugging and troubleshooting
* Improving code documentation and comments
* Supporting README and project documentation writing

All implementation decisions, code integration, testing, debugging, and final validation were performed manually by the project author.