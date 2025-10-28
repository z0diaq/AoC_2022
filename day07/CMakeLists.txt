# day07 executable
add_executable(day07)

target_sources(day07
    PRIVATE
        result.ixx
        part1.cpp
        part2.cpp
        shared.cpp
)

target_sources(day07 PRIVATE main.cpp)

target_link_libraries(day07 PRIVATE AoC)

target_include_directories(day07 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day07 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day07 PRIVATE cxx_std_20)
