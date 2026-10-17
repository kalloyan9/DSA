# Count Connected Components

A simple C++ project that counts connected components in a binary matrix using either BFS or a line-by-line component counter.

## Project overview

This project reads a matrix from standard input, validates the values, and counts the number of connected groups of `1` cells.

- `InputReader` reads dimensions and matrix rows and validates input values.
- `Matrix` stores the matrix and decides between two strategies:
  - BFS for smaller matrices
  - a linear scan for larger matrices
- `main.cpp` runs the program and prints the result.

## Current implementation

The code currently uses:

- `Matrix::solveBFS()` for small-to-medium matrices
- `Matrix::solveLine()` for larger matrices
- `std::queue` for BFS traversal
- `std::vector` for rows and visited state
- RAII-managed STL containers, so there are no manual `new`/`delete` calls and no explicit heap ownership to manage

## Algorithm

The matrix is treated as a grid of cells where neighbors are connected only in the 4 orthogonal directions:

- up
- down
- left
- right

Diagonal cells are not connected.

The BFS strategy visits every reachable `1` cell exactly once, while the line-based strategy detects a new component when a `1` cell is the first in its row or is connected to a zero in the previous row.

## Time and space complexity

For a matrix with `R` rows and `C` columns:

- BFS: O(R * C) time, O(R * C) extra space
  - `_matrix` stores the full matrix
  - `_visited` stores one boolean per cell
- Line-based scan: O(R * C) time, O(C) extra space
  - only two row buffers are kept at a time: `_prev_line` and `_curr_line`
  - each row is read once, processed, then moved into the previous-row buffer

This means the streaming scan is memory-efficient because it does not store the entire matrix in memory while processing it.

## Environment and toolchain

This project was developed and tested on a Windows machine using VS Code and MinGW GCC.

### Verified environment

| Component | Details |
|-----------|---------|
| OS | Windows 11 |
| Editor | Visual Studio Code |
| Compiler | MinGW-w64 g++ |
| C++ standard | C++17 |
| Build tools | GNU Make and direct g++ commands |
| Terminal | PowerShell / VS Code terminal |

### Example compiler command

```powershell
C:\msys64\mingw64\bin\g++.exe -Wall -Wextra -std=c++17 -ggdb -Iinclude src\InputReader.cpp src\Matrix.cpp src\main.cpp -o bin\main
```

## Build and run

### From the project folder

```powershell
make
```

This produces the executable in `bin/main`.

### Run the program

```powershell
./bin/main
```

### Input format

The first line contains the matrix dimensions:

```text
rows cols
```

Then each of the next `rows` lines contains `cols` values, each either `0` or `1`.

Example:

```text
3 3
1 1 1
0 0 0
1 1 1
```

Expected output:

```text
2
```

This means there are two disconnected components of `1` values.

## Notes on correctness and safety

### No manual memory leaks

The project does not use raw `new`/`delete` or manual memory allocation. All data is stored in STL containers such as `std::vector` and `std::queue`, which clean up automatically.

### No infinite loops

All loops are bounded by matrix dimensions or by the size of a queue:

- the BFS queue eventually empties because each visited cell is marked once
- the line-based scan iterates over each row and each column exactly once
- the input reader validates each matrix value before storing it

### Logic checks

The code validates:

- positive row and column counts
- input stream availability
- matrix values are only `0` or `1`
- BFS bounds before reading neighbors
- empty or invalid matrix cases

## Project files

- `include/Globals.hpp` — shared types and enums
- `include/InputReader.hpp` — input validation interface
- `include/Matrix.hpp` — matrix logic and class declaration
- `src/InputReader.cpp` — input parser implementation
- `src/Matrix.cpp` — BFS and line-based counting implementation
- `src/main.cpp` — program entry point
- `Makefile` — build automation
- `.vscode/tasks.json` — VS Code build tasks for Windows/MSYS2

## Troubleshooting

If VS Code builds the active file instead of the whole project, make sure the task compiles all source files together with the include directory. The safe project-level command is:

```powershell
g++.exe -Wall -Wextra -std=c++17 -ggdb -Iinclude src\InputReader.cpp src\Matrix.cpp src\main.cpp -o bin\main
```

This matches the project organization and prevents missing-header and undefined-reference errors.

## Summary

This project is a compact C++ solution for counting connected components in a binary matrix. It is built and tested in a Windows + VS Code + MinGW environment and relies on standard C++17 containers and safe, bounded traversal logic.
- ✅ Ubuntu 24.04 LTS (x86_64)
- ✅ Kernel 6.8.0-31-generic or compatible
- ✅ Glibc 2.39 (Ubuntu 24.04 standard)
- ✅ GNU Make 4.3
- ✅ cppcheck 2.13.0

### Expected Compatibility
- Linux distributions with GCC 11+ or Clang 12+ (C++17 support)
- macOS with Apple Clang 13+ (C++17 support)
- Windows with MinGW-w64 (GCC 11+) or MSVC 2019+
- Any POSIX-compliant system with C++17 compiler

## Unit Test Results Summary

```
Solver Tests:        25/25 passed ✅
InputReader Tests:    5/5  passed ✅
Logger Tests:         1/1  passed ✅
───────────────────────────────────
Total:               31/31 passed ✅
```

**Test Environment:**
- Compiler: g++ 13.3.0
- Platform: Linux Mint 22.3 (x86_64)
- C++ Standard: C++17 (-std=c++17)
- Optimization: -O2

*For more detailed analysis results, see [analysis_report.txt](analysis_report.txt)*

All modules compile without warnings and pass comprehensive unit test coverage.

## Development & AI Tools Used

### IDE & Editors
- **Microsoft VS Code** — Primary development environment
  - Integrated C++ IntelliSense
  - Easy C++ Projects extension for project scaffolding  
  - Built-in terminal for build/test execution
  - GitHub Copilot integration (v1.x)

### AI Assistance
- **GitHub Copilot** — Generative AI code assistance for:
  - Makefile build rule generation and multi-file C++ compilation
  - Unit test scaffolding, assertions, and comprehensive edge case generation
  - Improving documentation and README
  - Static code analysis interpretation and SOLID principle verification after the development process

### Additional Tools
- **cppcheck 2.13.0** — Automated static analysis and code quality verification
- **GNU Make 4.3** — Build system and task automation
