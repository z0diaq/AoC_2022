# day22 executable
add_executable(day22)

target_sources(day22
    PRIVATE
        monkey_map.ixx
        result.ixx
        solver.ixx
        tests.ixx
        types.ixx
)

target_sources(day22 PRIVATE main.cpp)

target_link_libraries(day22 PRIVATE AoC)

target_include_directories(day22 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day22 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day22 PRIVATE cxx_std_20)
