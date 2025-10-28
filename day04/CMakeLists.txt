# day04 executable
add_executable(day04)

target_sources(day04
    PRIVATE
        result.ixx
        result.cpp
)

target_sources(day04 PRIVATE main.cpp)

target_link_libraries(day04 PRIVATE AoC)

target_include_directories(day04 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day04 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day04 PRIVATE cxx_std_20)
