# day15 executable
add_executable(day15)

target_sources(day15
    PRIVATE
        point.ixx
        range.ixx
        result.ixx
        sensorInfo.ixx
        part1.cpp
        part2.cpp
        shared.cpp
)

target_sources(day15 PRIVATE main.cpp)

target_link_libraries(day15 PRIVATE AoC)

target_include_directories(day15 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day15 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day15 PRIVATE cxx_std_20)
