# day13 executable
add_executable(day13)

target_sources(day13
    PRIVATE
        extractor.ixx
        item.ixx
        packet.ixx
        result.ixx
        extractor.cpp
        item.cpp
        packet.cpp
        packetCompare.cpp
        part1.cpp
        part2.cpp
        shared.cpp
)

target_sources(day13 PRIVATE main.cpp)

target_link_libraries(day13 PRIVATE AoC)

target_include_directories(day13 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day13 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day13 PRIVATE cxx_std_20)
