# template executable
add_executable(template)

target_sources(template
    PRIVATE
        aoc_template.ixx
        result.ixx
        solver.ixx
        tests.ixx
        types.ixx
)

target_sources(template PRIVATE main.cpp)

target_link_libraries(template PRIVATE AoC)

target_include_directories(template PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(template PRIVATE ${Boost_LIBRARIES})

target_compile_features(template PRIVATE cxx_std_20)
