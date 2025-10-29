cmake_minimum_required(VERSION 3.28)

project(AoC_2022 CXX)

# C++20 modules support requires CMake 3.28+ and appropriate compiler
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# C++20 modules are still experimental in CMake
# GCC module support is limited - we'll use a hybrid approach
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.28")
    # Try experimental module support
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
    
    # Check if compiler supports module dependency scanning
    # GCC 11+ with proper module support requires special setup
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # GCC needs -fmodules-ts flag
        add_compile_options(-fmodules-ts)
        
        # GCC 13 doesn't fully support CMake's module scanning
        # We'll manually manage dependencies via source ordering
        set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
    else()
        # Try automatic scanning for other compilers
        set(CMAKE_CXX_SCAN_FOR_MODULES ON)
    endif()
endif()

# Compiler-specific flags
if(MSVC)
    add_compile_options(/W4 /WX /MP)
    add_compile_definitions(_CONSOLE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Oi /GL")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Werror)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

# Find Boost
find_package(Boost 1.70 REQUIRED)

# Add subdirectories
add_subdirectory(AoC)
add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
add_subdirectory(day05)
add_subdirectory(day06)
add_subdirectory(day07)
add_subdirectory(day08)
add_subdirectory(day09)
add_subdirectory(day10)
add_subdirectory(day11)
add_subdirectory(day12)
add_subdirectory(day13)
add_subdirectory(day14)
add_subdirectory(day15)
add_subdirectory(day16)
add_subdirectory(day17)
add_subdirectory(day18)
add_subdirectory(day19)
add_subdirectory(day20)
add_subdirectory(day21)
add_subdirectory(day22)
# add_subdirectory(day23)  # Add when implemented
# add_subdirectory(day24)  # Add when implemented
# add_subdirectory(day25)  # Add when implemented
add_subdirectory(template)
