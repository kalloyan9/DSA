# Count Connected Components

## Repo
Git repo for tracking my changes and project lifecycle:
git@github.com:kalloyan9/DSA.git

url for web GUI github view:
https://github.com/kalloyan9/DSA/tree/master/count-connected-components

## Overview

This solution counts connected components in a binary matrix using breadth-first search (BFS). The code separates responsibilities across modular classes designed for clarity, maintainability, and extensibility.

- `ConnectedComponentsSolver`: Core BFS algorithm and component counting
- `InputReader`: Validated input parsing and dimension checking
- `ILogger` / `ConsoleLogger`: Abstracted logging for testable I/O
- Thread-safe and exception-safe implementation with full RAII ownership

## Algorithm

- Uses breadth-first search (BFS)
- Visits each `1` cell exactly once
- Marks visited cells to prevent duplicate traversal
- Orthogonal neighbors only (up, down, left, right)
- No diagonal adjacency

## Complexity

**Time:** O(n × m)  
**Space:** O(n × m)

Where `n` = rows, `m` = columns. Storage uses compact `uint8_t` for both matrix and visited state.

## System & Environment

### Development Environment (Tested On)

| Component | Version | Details |
|-----------|---------|---------|
| **OS** | Linux Mint 22.3 | Based on Ubuntu 24.04 LTS |
| **Architecture** | x86_64 | 64-bit Intel/AMD processors |
| **Compiler** | g++ 13.3.0 | Ubuntu 13.3.0-6ubuntu2~24.04.1 |
| **C++ Standard** | C++17 | `-std=c++17` flag |
| **Build System** | GNU Make 4.3 | Incremental build automation |
| **Static Analyzer** | cppcheck 2.13.0 | Code quality & safety checks |
| **Compilation Flags** | `-Wall -Wextra -std=c++17 -O2` | Strict warnings + optimization |

### Kernel & System Info
- **Kernel:** Linux 6.8.0-31-generic (or compatible)
- **Glibc:** 2.39 (Ubuntu 24.04 standard)

## Build & Run

### Prerequisites

- GCC/G++ 9+ or Clang 10+ with C++17 support
- GNU Make 4.0+
- Standard C++ libraries (libstdc++ or libc++)

**Recommended:** GCC 11+ or Clang 12+ for best performance and diagnostics

### Build the main program

```bash
make
```

This produces `bin/main`.

### Run the main program

```bash
./bin/main
```

**Verified execution on:**
- Linux Mint 22.3 (x86_64)
- Ubuntu 24.04 LTS (x86_64)
- Compiler: g++ 13.3.0

Provide matrix dimensions (rows and columns) on the first line, then matrix values row by row (0 or 1 only).

Example input:
```
3 3
1 1 1
0 0 0
1 1 1
```

Output: `2 figures` (two separate components)

## Unit Tests

Build and run all unit tests:

```bash
make run-tests
```

### Individual test executables

- `./bin/solver_test` — ConnectedComponentsSolver unit tests (25 test cases)
- `./bin/inputreader_test` — InputReader validation tests (5 test cases)
- `./bin/logger_test` — ConsoleLogger unit tests
- `./bin/test` — Combined test suite

### Test Coverage

**ConnectedComponentsSolver Tests:**
- Empty matrix (all zeros)
- Single cell and small matrices (1×1, 2×2)
- Adjacent cells (horizontal and vertical)
- Non-adjacent cells (same row/column)
- Diagonal separation (no adjacency)
- Complex patterns (L-shaped, T-shaped, plus-shaped, spirals)
- State repeatability (countComponents() can be called multiple times)
- Bounds validation (out-of-range rejection)

**InputReader Tests:**
- Valid dimension parsing
- Zero dimension rejection
- Non-numeric input rejection
- Overflow detection (values > size_t max)
- Valid matrix value input
- Invalid matrix value rejection

**Result:** ✅ **All 30+ tests passed**

## OOP Principles & Design

### Encapsulation
- Private data members (`rows_`, `cols_`, `matrix_`, `visited_`)
- Public interfaces for state queries and mutations
- Bounds checking on all cell access

### Abstraction
- `ILogger` interface decouples logging implementation
- `InputReader` hides parsing complexity and validation
- `ConnectedComponentsSolver` exposes only essential BFS interface

### Single Responsibility
- `ConnectedComponentsSolver` handles only component counting
- `InputReader` handles only input parsing and validation
- `ConsoleLogger` handles only formatted output

### Exception Safety
- Constructor throws `std::invalid_argument` on zero dimensions
- `setCell()` throws `std::out_of_range` on bounds violation
- `InputReader` throws `InputError` on invalid input or parse failure
- All exceptions include descriptive messages

## Error Handling

- **Input validation:** Dimensions must be > 0 and ≤ size_t max
- **Type safety:** Matrix values validated as 0 or 1 only
- **Bounds checking:** Cell access bounds-checked at assignment
- **Stream safety:** Input stream failures detected and reported
- **Graceful degradation:** Clear error messages for all failure cases

## Static Code Analysis

### Build Configuration

- **Compiler:** g++ 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04.1)
- **Compilation Flags:** `-Wall -Wextra -std=c++17 -O2`
- **C++ Standard:** C++17 (ISO/IEC 14882:2017)
- **Optimization Level:** O2 (balanced speed/size)

### cppcheck Analysis (v2.13.0)

```
Static Analyzer:   cppcheck 2.13.0
Active Checkers:   161/592
Warnings:          0
Errors:            0
Analysis Status:   ✅ PASS
```

### Code Quality Verification

| Criterion | Status | Details |
|-----------|--------|---------|
| Memory Safety | ✅ PASS | No leaks; RAII-managed STL containers |
| No Infinite Loops | ✅ PASS | BFS uses queue + visited tracking |
| OOP Practices | ✅ PASS | Encapsulation, single responsibility, clear interfaces |
| Edge Cases | ✅ PASS | Empty/single-cell/large matrices handled |
| Bounds Checking | ✅ PASS | Input validation + array access protection |
| Exception Safety | ✅ PASS | Strong guarantee on all operations |
| Const Correctness | ✅ PASS | Read-only methods marked const |
| Resource Ownership | ✅ PASS | Clear ownership, no shared pointers needed |

## Tools & Credits

### Compiler & Build Toolchain
- **G++ 13.3.0** (Ubuntu 13.3.0-6ubuntu2~24.04.1) — C++17 compilation with strict diagnostics
- **GNU Make 4.3** (built for x86_64-pc-linux-gnu) — Task automation and incremental builds
- **Linker:** ld (GNU binutils) — ELF binary linking for Linux x86_64

### Testing & Analysis
- **GCC/Clang** — Compilation with `-Wall -Wextra` for maximum diagnostics coverage
- **cppcheck 2.13.0** — Static analysis engine with 161 active checkers for code quality and safety verification
- **Custom Unit Test Framework** — Assert-based testing with stdout logging (31+ test cases)

### C++ Standard Libraries Used
- `<queue>` — BFS queue data structure
- `<vector>` — Dynamic 2D matrix storage
- `<stdexcept>` — Exception types for error handling
- `<limits>` — std::numeric_limits for overflow detection
- `<iostream>` — Standard I/O for CLI
- `<sstream>` — String streams for input parsing
- `<cassert>` — Test assertions
- `<cstddef>` — std::size_t type definitions
- `<cstdint>` — Fixed-width integer types (uint8_t)
- `<iosfwd>` — Forward declarations for ostream/istream

## Platform Compatibility

### Tested & Verified On
- ✅ Linux Mint 22.3 (x86_64) with g++ 13.3.0
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
