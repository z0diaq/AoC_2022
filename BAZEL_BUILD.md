# Bazel Build System for AoC 2022

This repository has been converted from Visual Studio to Bazel build system while maintaining the same project structure.

## Prerequisites

- **Bazel**: Install Bazel 7.0 or later from [bazel.build](https://bazel.build/install)
- **C++ Compiler**: GCC 11+ or Clang 14+ with C++20 support
- **Git**: For dependency management

## Project Structure

The Bazel build maintains the same structure as the Visual Studio solution:

- **AoC/** - Shared library with common utilities (equivalent to AoC.vcxproj static library)
- **day01/ - day25/** - Individual day solutions (equivalent to day01.vcxproj - day25.vcxproj executables)
- **template/** - Template project for new days

## Building Projects

### Build a specific day

```bash
bazel build //day01:day01
bazel build //day13:day13
```

### Build all days at once

```bash
bazel build //:all_days
```

### Build the shared AoC library

```bash
bazel build //AoC:aoc_lib
```

### Build template project

```bash
bazel build //template:template
```

## Running Projects

### Run a specific day's solution

```bash
bazel run //day01:day01
```

### Run with arguments

```bash
bazel run //day01:day01 -- arg1 arg2
```

## Build Configurations

The `.bazelrc` file provides several build configurations:

### Debug build (with symbols)

```bash
bazel build --config=debug //day01:day01
```

### Release build (optimized)

```bash
bazel build --config=release //day01:day01
```

### Fast build (default, minimal optimization)

```bash
bazel build //day01:day01
# or explicitly
bazel build --config=fastbuild //day01:day01
```

## Dependencies

The project uses the following external dependencies via Bazel Central Registry:

- **rules_cc** (0.0.9) - C++ build rules
- **googletest** (1.14.0) - Testing framework
- **boost** (1.83.0) - Boost C++ libraries

Dependencies are automatically fetched by Bazel on first build.

## Compiler Flags

The build uses the following C++ configuration:

- **Standard**: C++20 (`-std=c++20`)
- **Warnings**: `-Wall -Wextra -Werror`
- **Modules**: Experimental C++20 modules support enabled

## File Locations

### Source Files

All source files remain in their original locations:
- `day01/main.cpp`, `day01/result.ixx`, etc.
- Input data files (`*.txt`) stay alongside source code

### Build Artifacts

Bazel creates symlinks in the project root:
- `bazel-bin/` - Compiled binaries
- `bazel-out/` - Build outputs
- `bazel-aoc_2022/` - Project root symlink
- `bazel-testlogs/` - Test logs

These are gitignored and should not be committed.

## Common Commands

```bash
# Clean build artifacts
bazel clean

# Deep clean (removes external dependencies cache)
bazel clean --expunge

# View dependency graph for a target
bazel query --output=graph //day01:day01

# List all targets
bazel query //...

# Build everything
bazel build //...

# Test everything (if tests are configured)
bazel test //...
```

## Comparison with Visual Studio

| Visual Studio | Bazel |
|---------------|-------|
| `AoC.vcxproj` (Static Library) | `//AoC:aoc_lib` |
| `day01.vcxproj` (Executable) | `//day01:day01` |
| Solution Build | `bazel build //:all_days` |
| Debug Configuration | `bazel build --config=debug` |
| Release Configuration | `bazel build --config=release` |
| Rebuild All | `bazel clean && bazel build //...` |

## Notes

- **C++ Modules**: The project uses `.ixx` module interface files. Bazel's experimental C++ modules support is enabled.
- **Boost**: Requires Boost for filesystem and algorithm utilities
- **Data Files**: Test input files (*.txt) are automatically included via `data = glob(["*.txt"])` in each BUILD file
- **Cross-platform**: Works on Linux, macOS, and Windows

## Troubleshooting

### Module compilation errors

If you encounter C++20 module compilation errors, ensure your compiler supports modules:
- GCC: Version 11 or later
- Clang: Version 14 or later

### Missing dependencies

If dependencies fail to download:
```bash
bazel sync --configure
```

### Cache issues

Clear the cache if builds behave unexpectedly:
```bash
bazel clean --expunge
```
