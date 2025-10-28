# day03 executable
add_executable(day03)

target_sources(day03
    PRIVATE
        result.ixx
        result.cpp
)

target_sources(day03 PRIVATE main.cpp)

target_link_libraries(day03 PRIVATE AoC)

target_include_directories(day03 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day03 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day03 PRIVATE cxx_std_20)
