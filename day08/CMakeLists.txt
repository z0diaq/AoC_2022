# day08 executable
add_executable(day08)

target_sources(day08
    PRIVATE
        result.ixx
        part1.cpp
        part2.cpp
)

target_sources(day08 PRIVATE main.cpp)

target_link_libraries(day08 PRIVATE AoC)

target_include_directories(day08 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day08 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day08 PRIVATE cxx_std_20)
