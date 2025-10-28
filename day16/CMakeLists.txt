# day16 executable
add_executable(day16)

target_sources(day16
    PRIVATE
        minDistances.ixx
        result.ixx
        valveInfo.ixx
        part1.cpp
        part2.cpp
        resultCompute.cpp
        resultPrepare.cpp
)

target_sources(day16 PRIVATE main.cpp)

target_link_libraries(day16 PRIVATE AoC)

target_include_directories(day16 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day16 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day16 PRIVATE cxx_std_20)
