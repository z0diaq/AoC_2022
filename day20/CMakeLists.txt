# day20 executable
add_executable(day20)

target_sources(day20
    PRIVATE
        gps.ixx
        result.ixx
        solver.ixx
        tests.ixx
        types.ixx
)

target_sources(day20 PRIVATE main.cpp)

target_link_libraries(day20 PRIVATE AoC)

target_include_directories(day20 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day20 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day20 PRIVATE cxx_std_20)
