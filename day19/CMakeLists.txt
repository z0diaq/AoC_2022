# day19 executable
add_executable(day19)

target_sources(day19
    PRIVATE
        blockedRobots.ixx
        blueprint.ixx
        result.ixx
        robotCost.ixx
        state.ixx
        types.ixx
        blueprint.cpp
        part1.cpp
        part2.cpp
        robotCost.cpp
        shared.cpp
        solver.cpp
        state.cpp
)

target_sources(day19 PRIVATE main.cpp)

target_link_libraries(day19 PRIVATE AoC)

target_include_directories(day19 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day19 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day19 PRIVATE cxx_std_20)
