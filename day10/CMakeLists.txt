# day10 executable
add_executable(day10)

target_sources(day10
    PRIVATE
        result.ixx
        part1.cpp
        part2.cpp
        shared.cpp
)

target_sources(day10 PRIVATE main.cpp)

target_link_libraries(day10 PRIVATE AoC)

target_include_directories(day10 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day10 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day10 PRIVATE cxx_std_20)
