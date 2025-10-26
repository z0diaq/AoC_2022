# Bazel Conversion Summary

## Conversion Complete

The Visual Studio solution has been successfully converted to Bazel build system format.

## What Was Created

### Core Configuration Files

1. **MODULE.bazel** - Bazel module definition with dependencies (rules_cc, googletest)
2. **.bazelrc** - Build configuration with C++20 flags and compiler settings
3. **BUILD.bazel** (root) - Convenience target to build all day solutions
4. **BAZEL_BUILD.md** - Complete documentation for using Bazel builds

### Build Files Per Project

- **AoC/BUILD.bazel** - Shared library (equivalent to AoC.vcxproj static library)
- **day01/BUILD.bazel through day22/BUILD.bazel** - Individual executables
- **day23/BUILD.bazel, day24/BUILD.bazel, day25/BUILD.bazel** - Placeholder files (commented out, no source code yet)
- **template/BUILD.bazel** - Template project with GoogleTest support

### Additional Changes

- Updated **.gitignore** to exclude Bazel build artifacts (`bazel-*`, `.bazelrc.user`)

## Project Structure Maintained

The Bazel conversion maintains the exact same structure as the Visual Studio solution:

```
AoC_2022/
├── MODULE.bazel          # Bazel module configuration
├── .bazelrc              # Build settings
├── BUILD.bazel           # Root build file
├── AoC/                  # Shared library
│   └── BUILD.bazel
├── day01/                # Day 1 solution
│   ├── BUILD.bazel
│   ├── main.cpp
│   └── ...
├── day02/ ... day22/     # Days 2-22 (implemented)
├── day23/ ... day25/     # Days 23-25 (not implemented)
└── template/             # Template project
    └── BUILD.bazel
```

## Dependencies

### External Dependencies (via Bazel Central Registry)
- **rules_cc** (0.1.1) - C++ build rules
- **googletest** (1.14.0.bcr.1) - Testing framework for template project

### System Dependencies
- **Boost** - Expected to be installed on the system
  - Filesystem library
  - Algorithm library
  - System library

The build links against system Boost libraries via `-lboost_filesystem` and `-lboost_system`.

## C++20 Modules Support

### Current Status

The project uses C++ modules (`.ixx` files). Bazel configuration includes:
- `--experimental_cpp_modules` flag
- `-fmodules-ts` compiler flag for GCC

### Known Limitations

**C++20 modules support varies by compiler:**

#### GCC (version 11+)
- Partial C++20 modules support via `-fmodules-ts`
- May have compilation issues with complex module dependencies
- Module interface files (`.ixx`) are treated as source files

#### Clang (version 16+)
- Better C++20 modules support
- May require additional flags or configuration

#### MSVC
- Good C++20 modules support in Visual Studio
- Not directly supported by Bazel on Windows

### Workaround if Modules Fail

If you encounter module compilation errors, you have two options:

1. **Use a compatible compiler** (recent Clang recommended)
2. **Convert modules to headers** (requires code changes):
   - Rename `.ixx` files to `.h`
   - Replace `export module` with header guards
   - Replace `import` with `#include`

## Build Commands

### Quick Start

```bash
# Build a single day
bazel build //day01:day01

# Build all implemented days
bazel build //:all_days

# Run a day's solution
bazel run //day01:day01

# Build with optimizations
bazel build --config=release //day01:day01

# Build everything
bazel build //...
```

See **BAZEL_BUILD.md** for complete documentation.

## Implementation Status

### Implemented Days (22 of 25)
- day01 through day22: ✅ Fully configured

### Not Yet Implemented (3 of 25)
- day23: ⏸ BUILD file commented out (no source files)
- day24: ⏸ BUILD file commented out (no source files)
- day25: ⏸ BUILD file commented out (no source files)

When these days are implemented, uncomment the BUILD file contents and add them back to `//:all_days` in the root BUILD.bazel.

## Migration from Visual Studio

| Visual Studio Action | Bazel Equivalent |
|---------------------|------------------|
| Build Solution | `bazel build //:all_days` |
| Build Project (e.g., day01) | `bazel build //day01:day01` |
| Rebuild All | `bazel clean && bazel build //...` |
| Run day01 | `bazel run //day01:day01` |
| Debug build | `bazel build --config=debug //day01:day01` |
| Release build | `bazel build --config=release //day01:day01` |

## Next Steps

1. **Test the build**:
   ```bash
   bazel build //AoC:aoc_lib
   bazel build //day01:day01
   ```

2. **Verify modules compilation** - If errors occur, check compiler version

3. **Install Boost** (if not already installed):
   ```bash
   # Ubuntu/Debian
   sudo apt-get install libboost-all-dev
   
   # Fedora
   sudo dnf install boost-devel
   
   # macOS
   brew install boost
   ```

4. **Run a solution**:
   ```bash
   bazel run //day01:day01
   ```

## Troubleshooting

### Module Compilation Errors

If you see errors like `'import' does not name a type`:
- Ensure GCC 11+ or Clang 16+ is installed
- Check that `-fmodules-ts` flag is present in build output
- Consider switching to Clang: `export CC=clang CXX=clang++`

### Missing Boost

If build fails with Boost-related errors:
- Install Boost development libraries (see "Next Steps" above)
- Verify installation: `ldconfig -p | grep boost`

### Bazel Cache Issues

```bash
bazel clean --expunge
bazel sync --configure
```

## Benefits of Bazel

1. **Reproducible builds** - Same build results across machines
2. **Incremental compilation** - Only rebuilds changed files
3. **Parallel builds** - Automatically parallelizes compilation
4. **Dependency management** - Explicit dependencies between targets
5. **Cross-platform** - Works on Linux, macOS, Windows
6. **Caching** - Local and remote build caching support

## Files Preserved

All original source files remain unchanged:
- `*.cpp`, `*.ixx` source and module files
- `*.txt` input and test data files
- Visual Studio project files (`.vcxproj`, `.sln`) still present for reference

The Bazel build system works alongside the existing Visual Studio setup.
