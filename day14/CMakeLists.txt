# day14 executable
add_executable(day14)

target_sources(day14
    PRIVATE
        result.ixx
        scan.ixx
        part1.cpp
        part2.cpp
        scan.cpp
        scanAnalyze.cpp
        scanPrepare.cpp
        shared.cpp
)

target_sources(day14 PRIVATE main.cpp)

target_link_libraries(day14 PRIVATE AoC)

target_include_directories(day14 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day14 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day14 PRIVATE cxx_std_20)
