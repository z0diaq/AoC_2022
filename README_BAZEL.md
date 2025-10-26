# Bazel Build System - Quick Reference

This repository now supports Bazel builds alongside the original Visual Studio solution.

## Quick Start

```bash
# Verify Bazel can see all targets
bazel query //...

# Build the shared library
bazel build //AoC:aoc_lib

# Build and run a specific day
bazel build //day01:day01
bazel run //day01:day01

# Build all implemented days (day01-day22)
bazel build //:all_days
```

## Common Commands

```bash
# Build specific day with optimizations
bazel build --config=release //day05:day05

# Build in debug mode
bazel build --config=debug //day10:day10

# Clean build artifacts
bazel clean

# Build everything
bazel build //...

# Query dependencies of a target
bazel query --output=graph //day01:day01
```

## Directory Structure

```
├── MODULE.bazel                 # Bazel module configuration
├── .bazelrc                     # Build flags and settings
├── BUILD.bazel                  # Root: all_days target
├── AoC/BUILD.bazel              # Shared library
├── day01/BUILD.bazel            # Day 1 executable
├── day02/BUILD.bazel            # Day 2 executable
│   ...
├── day22/BUILD.bazel            # Day 22 executable
└── template/BUILD.bazel         # Template with GoogleTest
```

## Documentation

- **BAZEL_BUILD.md** - Complete Bazel usage guide
- **BAZEL_CONVERSION_NOTES.md** - Detailed conversion information and troubleshooting

## Requirements

- Bazel 7.0+
- GCC 11+ or Clang 16+ (for C++20 modules)
- Boost development libraries (system-installed)

## Installation

### Bazel
```bash
# See https://bazel.build/install
```

### Boost (if not installed)
```bash
# Ubuntu/Debian
sudo apt-get install libboost-all-dev

# Fedora
sudo dnf install boost-devel

# macOS
brew install boost
```

## Project Status

- ✅ **22 days implemented** (day01-day22)
- ⏸ **3 days pending** (day23-day25 - no source files yet)

## Notes

- Original Visual Studio files (`.vcxproj`, `.sln`) remain unchanged
- Data files (`*.txt`) are included automatically via `glob(["*.txt"])`
- C++20 modules (`.ixx` files) require recent compiler with `-fmodules-ts` support
- Boost libraries are linked from system installation

---

For detailed information, see **BAZEL_BUILD.md** and **BAZEL_CONVERSION_NOTES.md**.
