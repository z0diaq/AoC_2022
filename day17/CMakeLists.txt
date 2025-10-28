# day17 executable
add_executable(day17)

target_sources(day17
    PRIVATE
        jetPattern.ixx
        result.ixx
        rock.ixx
        rockShape.ixx
        rocksTower.ixx
        jetPattern.cpp
        part1.cpp
        part2.cpp
        rock.cpp
        rockShape.cpp
        rocksTower.cpp
        shared.cpp
)

target_sources(day17 PRIVATE main.cpp)

target_link_libraries(day17 PRIVATE AoC)

target_include_directories(day17 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day17 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day17 PRIVATE cxx_std_20)
