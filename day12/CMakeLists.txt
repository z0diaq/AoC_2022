# day12 executable
add_executable(day12)

target_sources(day12
    PRIVATE
        result.ixx
        helpers.cpp
        part1.cpp
        part2.cpp
        shared.cpp
)

target_sources(day12 PRIVATE main.cpp)

target_link_libraries(day12 PRIVATE AoC)

target_include_directories(day12 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day12 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day12 PRIVATE cxx_std_20)
