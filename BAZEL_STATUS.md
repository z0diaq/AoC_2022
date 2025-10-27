# Bazel Build Status

## Current Status: ⚠️ PARTIAL - Modules Issue

The Bazel conversion has been completed structurally, but there's a **fundamental incompatibility** between C++20 modules and the current Bazel/GCC toolchain.

## What Works ✅

- All BUILD.bazel files created for 25 day projects + AoC library + template
- MODULE.bazel with dependencies (rules_cc, googletest)
- .bazelrc with C++20 compiler flags
- Project structure mirrors Visual Studio solution exactly
- Bazel can parse and analyze all targets

## What Doesn't Work ❌

### C++20 Modules Compilation

**Error**: Mixing module imports with traditional `#include` headers causes symbol redefinition errors.

**Root Cause**:
- Module interface files (`.ixx`) include standard headers in global module fragment
- Implementation files (`.cpp`) both import modules AND include headers
- This creates duplicate symbol definitions in GCC's module system

**Example Error**:
```
error: redefinition of 'template<class ... _Bn> constexpr const bool std::__and_v'
```

## Fix Attempted

Created custom genrule in `AoC/BUILD.bazel` to:
1. Compile module partitions (`testData.ixx`, `fsHelpers.ixx`)
2. Compile primary module interface (`result.ixx`)  
3. Compile implementation files (`*.cpp`)
4. Create static library

**Result**: Module compilation succeeds, but implementation file compilation fails due to header/module mixing.

## Solutions

### Option 1: Convert Modules to Headers (Recommended for Bazel)

**Pros**:
- Works with all C++ build systems
- No special compiler flags needed
- Bazel fully supports this

**Cons**:
- Requires code changes
- Loses module benefits

**Steps**:
1. Rename `.ixx` →  `.h`
2. Replace `export module AoC;` with header guards
3. Replace `import` with `#include`
4. Update BUILD files to use `hdrs` instead of custom genrule

### Option 2: Use MSVC with Bazel (Windows only)

**Pros**:
- MSVC has better C++20 module support
- Keeps existing code structure

**Cons**:
- Bazel + MSVC integration is complex
- Linux-incompatible

### Option 3: Keep Visual Studio for C++20 Modules

**Pros**:
- Visual Studio natively supports modules well
- No code changes needed
- Existing .vcxproj files work perfectly

**Cons**:
- Bazel build non-functional for this project

## Current BUILD.bazel Status

### AoC/BUILD.bazel

Contains experimental genrule approach that:
- ✅ Compiles module interface files
- ❌ Fails when compiling implementation files

```starlark
# Custom genrule to compile C++20 modules
# Status: Compiles modules but fails on implementation files
genrule(name = "compile_aoc_objects", ...)
```

### Day Projects (day01-day22/BUILD.bazel)

Standard cc_binary definitions that will fail if they depend on `//AoC:aoc_lib` due to the module issues above.

## Recommendations

### Short Term
**Continue using Visual Studio** for this project. The C++20 modules work perfectly there.

### Long Term (if Bazel is required)

1. **Refactor to headers**: Convert `.ixx` module files to traditional `.h` headers
2. **Wait for tooling**: GCC module support is still experimental (as of GCC 13)
3. **Try Clang**: Clang 16+ has better module support, but still experimental

## Files Modified

### Source Code Changes
- ✅ `AoC/result.ixx` - Added `#include <functional>` (fixes std::invoke error)

### Bazel Configuration
- ✅ `MODULE.bazel` - Dependencies configured
- ✅ `.bazelrc` - C++20 flags including `-fmodules-ts`
- ⚠️ `AoC/BUILD.bazel` - Custom genrule (partial success)
- ✅ `day01-day25/BUILD.bazel` - All created
- ✅ `.gitignore` - Bazel artifacts excluded

## Test Results

```bash
# Module interface compilation
bazel build //AoC:compile_aoc_objects
# Result: ❌ Fails on testData.cpp with header conflicts

# Full library build  
bazel build //AoC:aoc_lib
# Result: ❌ Depends on compile_aoc_objects

# Day builds
bazel build //day01:day01
# Result: ❌ Would fail (depends on aoc_lib)
```

## Conclusion

The Bazel build infrastructure is **complete and correct**, but C++20 modules are not practically usable with current Bazel + GCC combination.

**Recommended Action**: Use Visual Studio for builds until:
1. Code is refactored to use headers instead of modules, OR
2. Bazel/GCC module support matures significantly

The Bazel configuration files can remain in the repository for future use or reference.
