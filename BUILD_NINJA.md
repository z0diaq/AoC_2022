# Building with Ninja

This project has been converted from Visual Studio to use CMake with Ninja as the build system. This document explains how to build the project.

## Prerequisites

### Required Software

1. **CMake 3.28 or higher** - Required for C++20 module support
   ```bash
   cmake --version  # Check your version
   ```

2. **Ninja build system**
   ```bash
   # Ubuntu/Debian
   sudo apt install ninja-build
   
   # Fedora/RHEL
   sudo dnf install ninja-build
   
   # Arch Linux
   sudo pacman -S ninja
   ```

3. **C++20 compatible compiler**
   - GCC 11+ with module support
   - Clang 16+ with module support
   - MSVC 2022 (17.4+) with `/std:c++20` and module support

4. **Boost Libraries 1.70+**
   - The project uses Boost for string algorithms and lexical cast
   - Ensure Boost is installed and findable by CMake

### Checking Compiler Module Support

**GCC:**
```bash
g++ --version  # Should be 11 or higher
```

**Clang:**
```bash
clang++ --version  # Should be 16 or higher
```

## Quick Start

### 1. Configure the Build

```bash
./configure.sh [Debug|Release]
```

This will:
- Check for required tools (CMake, Ninja)
- Create a `build/` directory
- Generate Ninja build files
- Generate `compile_commands.json` for IDE integration

Example:
```bash
./configure.sh Debug    # Configure for debug build
./configure.sh Release  # Configure for release build
```

### 2. Build the Project

```bash
./build.sh [target]
```

Build all targets:
```bash
./build.sh
```

Build a specific day:
```bash
./build.sh day01
./build.sh day13
```

### 3. Run Executables

After building, executables are located in the `build/` directory:

```bash
./build/day01/day01
./build/day13/day13
```

## Manual Build Commands

If you prefer to use CMake and Ninja directly:

### Configure

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
```

### Build

```bash
# Build all
ninja -C build

# Build specific target
ninja -C build day01

# Parallel build (use N cores)
ninja -C build -j N

# Verbose build
ninja -C build -v
```

### Clean

```bash
ninja -C build clean
```

### Reconfigure

```bash
rm -rf build
./configure.sh
```

## Project Structure

The project is organized as follows:

```
AoC_2022/
├── CMakeLists.txt          # Root CMake configuration
├── configure.sh            # Configuration script
├── build.sh                # Build script
├── AoC/                    # Shared library
│   ├── CMakeLists.txt
│   ├── result.ixx          # C++20 module
│   ├── result.cpp
│   ├── fsHelpers.ixx       # C++20 module
│   ├── testData.ixx        # C++20 module
│   └── testData.cpp
├── day01/                  # Day 1 solution
│   ├── CMakeLists.txt
│   ├── main.cpp
│   └── result.ixx          # Day-specific module
├── day02/                  # Day 2 solution
│   └── ...
└── ...
```

## Build Targets

- **all** - Build all targets (default)
- **AoC** - Build the shared AoC library
- **day01** through **day22** - Build specific day executables
- **template** - Build the template executable

## C++20 Modules

This project uses C++20 modules (`.ixx` files). Key points:

1. **Module Interface Files (`.ixx`)**: Exported interface of modules
2. **Module Implementation Files (`.cpp`)**: Non-exported implementation
3. **Build Order**: CMake automatically handles module dependencies

### Module Structure

- **AoC module**: Base library providing common functionality
  - `AoC:test_data` - Test data handling
  - `AoC:fs_helpers` - File system utilities
  
- **Day-specific modules**: Each day exports its own module (e.g., `calorie_counting`)

## Compiler-Specific Notes

### GCC

GCC 11+ supports modules but may require additional flags. The CMakeLists.txt handles this automatically.

### Clang

Clang 16+ has experimental module support. Ensure you have a recent version.

### MSVC

MSVC 2022 (17.4+) has good module support. Use the Visual Studio Developer Command Prompt on Windows.

## Troubleshooting

### CMake Version Too Old

If you see:
```
CMake Error: CMake was unable to find a build program corresponding to "Ninja"
```

Update CMake to 3.28+:
```bash
# Ubuntu (using Kitware's APT repository)
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ focal main'
sudo apt update
sudo apt install cmake
```

### Boost Not Found

If CMake cannot find Boost:

1. Install Boost:
   ```bash
   # Ubuntu/Debian
   sudo apt install libboost-all-dev
   
   # Fedora
   sudo dnf install boost-devel
   ```

2. Or specify Boost location:
   ```bash
   cmake -S . -B build -G Ninja -DBOOST_ROOT=/path/to/boost
   ```

### Module Compilation Errors

Ensure your compiler supports C++20 modules:

```bash
# GCC
g++ -std=c++20 -fmodules-ts --version

# Clang
clang++ -std=c++20 -fmodules --version
```

### Ninja Not Found

Install Ninja:
```bash
# Ubuntu/Debian
sudo apt install ninja-build

# Fedora
sudo dnf install ninja-build
```

## IDE Integration

### Visual Studio Code

1. Install the CMake Tools extension
2. Open the workspace
3. Run "CMake: Configure" from the command palette
4. Select "Ninja" as the kit
5. Build using "CMake: Build"

The `compile_commands.json` file is generated for IntelliSense support.

### CLion

CLion has native CMake support:
1. Open the project
2. CLion will detect CMakeLists.txt automatically
3. Select "Ninja" as the build tool in Settings → Build, Execution, Deployment → CMake

## Performance

Ninja is faster than Make because it:
- Tracks dependencies more accurately
- Minimizes redundant work
- Supports better parallelization

Expected build times (with 8 cores):
- Clean build: ~30-60 seconds
- Incremental build: ~2-10 seconds

## Comparison to Visual Studio

| Feature | Visual Studio | CMake + Ninja |
|---------|---------------|---------------|
| Platform | Windows only | Cross-platform |
| Build Speed | Moderate | Fast |
| Module Support | Good (MSVC) | Excellent |
| Parallelization | Good | Excellent |
| IDE Integration | Native | Via extensions |
| Command-line | MSBuild | Ninja |

## Advanced Usage

### Custom Build Directory

```bash
cmake -S . -B my_build -G Ninja
ninja -C my_build
```

### Specify Compiler

```bash
CXX=g++-12 ./configure.sh
# or
CXX=clang++-16 ./configure.sh
```

### Build with Specific Core Count

```bash
ninja -C build -j 4  # Use 4 cores
```

### Generate Build Graph

```bash
ninja -C build -t graph | dot -Tpng -o build_graph.png
```

## Migration Notes

This project was migrated from Visual Studio (`.sln`, `.vcxproj`) to CMake + Ninja. The original Visual Studio files are kept for reference but are no longer maintained.

### Changes Made

1. ✅ Created `CMakeLists.txt` files for each subdirectory
2. ✅ Configured C++20 module support
3. ✅ Set up Boost dependency
4. ✅ Added build scripts (`configure.sh`, `build.sh`)
5. ✅ Maintained same project structure
6. ✅ Preserved all compiler flags (warnings as errors, optimization levels)

### What Stayed the Same

- All source code (`.cpp`, `.ixx` files)
- Project structure and organization
- Module organization and dependencies
- Boost dependency

## Contributing

When adding a new day:

1. Create a new `dayXX/` directory
2. Add source files
3. Run `python3 generate_cmake.py` to generate CMakeLists.txt
4. Update root CMakeLists.txt to add the new subdirectory
5. Reconfigure: `./configure.sh`
6. Build: `./build.sh dayXX`
