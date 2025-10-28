# day11 executable
add_executable(day11)

target_sources(day11
    PRIVATE
        result.ixx
        monkey.cpp
        monkeyOperations.cpp
        part1.cpp
        part2.cpp
        shared.cpp
)

target_sources(day11 PRIVATE main.cpp)

target_link_libraries(day11 PRIVATE AoC)

target_include_directories(day11 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day11 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day11 PRIVATE cxx_std_20)
