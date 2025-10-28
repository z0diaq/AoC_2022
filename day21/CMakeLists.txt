# day21 executable
add_executable(day21)

target_sources(day21
    PRIVATE
        monkey_math.ixx
        result.ixx
        solver.ixx
        tests.ixx
        types.ixx
)

target_sources(day21 PRIVATE main.cpp)

target_link_libraries(day21 PRIVATE AoC)

target_include_directories(day21 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day21 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day21 PRIVATE cxx_std_20)
