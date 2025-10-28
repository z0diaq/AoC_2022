# day18 executable
add_executable(day18)

target_sources(day18
    PRIVATE
        cube.ixx
        grid.ixx
        result.ixx
        cube.cpp
        grid.cpp
        part1.cpp
        part2.cpp
        shared.cpp
)

target_sources(day18 PRIVATE main.cpp)

target_link_libraries(day18 PRIVATE AoC)

target_include_directories(day18 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day18 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day18 PRIVATE cxx_std_20)
