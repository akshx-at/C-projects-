# C Projects

Collection of programming assignments completed in C as part of coursework at the University of Illinois Urbana-Champaign.

## Overview

This repository groups together multiple machine problems and lab-style assignments that cover core systems programming skills: algorithm design, data structures, testing, file processing, game logic, and low-level debugging. Each `mp*` directory is effectively its own standalone assignment with its own sources, sample inputs, and in several cases a local `Makefile`.

## What This Repository Contains

- Assembly-based introductory exercises in the early MPs
- Standalone C assignments with separate compilation units and headers
- Algorithmic problems such as semiprimes, Sudoku, mazes, sparse matrices, and floorplanning
- Small interactive or simulation-style programs such as Game of Life
- Coursework artifacts preserved in their original assignment-oriented layout

## Repository Layout

```text
C-projects-/
├── mp1/   # Introductory assembly exercises and test inputs
├── mp2/   # Additional assembly work
├── mp3/   # Early C programming assignment
├── mp4/   # Semiprime-related program and headers
├── mp5/   # Multi-file C assignment with tests
├── mp6/   # Game of Life implementation
├── mp7/   # Sudoku solver
├── mp8/   # Terminal game logic
├── mp9/   # Maze solver
├── mp10/  # Sparse matrix assignment
├── mp11/  # Floorplanning project
└── mp12/  # Geometry/checking utilities
```

## Working With The Code

There is not a single top-level build for the entire repository. Instead, most assignments are designed to be built independently from within their own folders.

Typical workflow:

```bash
cd mp7
make
./mp7
```

If a directory does not include a `Makefile`, compile it directly with `gcc` using the source files in that folder.

## Notes

- Some directories include preserved build outputs from the original coursework submissions.
- File naming follows the original class conventions to make it easier to map each folder back to the assignment prompt.
- This repository is best read as an archive of individual programming projects rather than as a single unified application.

## Skills Demonstrated

- C programming
- Basic assembly programming
- Problem decomposition
- Data structures and algorithms
- Testing against provided input/output cases
- Working within assignment constraints and starter code layouts
