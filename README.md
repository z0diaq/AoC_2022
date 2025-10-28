# AoC_2022

Advent of Code 2022

my C++ solutions for puzzles from https://adventofcode.com/2022

more for practicing features from latest standards (i.e. modules from C++20, std algorithms and boost) than providing fastest/simplest possible solutions - readability over performance

Code comments and solutions improvements are welcomed!

## Build System

This project uses **CMake with Ninja** for building. C++20 modules are fully supported.

### Quick Start

```bash
./configure.sh    # Configure the build (Debug by default)
./build.sh        # Build all targets
```

For detailed build instructions, see **[BUILD_NINJA.md](BUILD_NINJA.md)**

### Requirements
- CMake 3.28+
- Ninja build system
- C++20 compatible compiler (GCC 11+, Clang 16+, or MSVC 2022)
- Boost 1.70+

setup instructions in template\\readme_setup.txt

note: don't put input publicly with solutions -> https://www.reddit.com/r/adventofcode/wiki/faqs/copyright/inputs/

personal goals:

* source files not longer than 100 lines but easy to read
* close to zero comments - code should describe itself
* KISS - keep it stupid simple