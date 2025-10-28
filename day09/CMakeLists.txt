# day09 executable
add_executable(day09)

target_sources(day09
    PRIVATE
        result.ixx
        part1.cpp
        part2.cpp
        shared.cpp
)

target_sources(day09 PRIVATE main.cpp)

target_link_libraries(day09 PRIVATE AoC)

target_include_directories(day09 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day09 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day09 PRIVATE cxx_std_20)
