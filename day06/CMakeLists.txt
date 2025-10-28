# day06 executable
add_executable(day06)

target_sources(day06
    PRIVATE
        result.ixx
        result.cpp
)

target_sources(day06 PRIVATE main.cpp)

target_link_libraries(day06 PRIVATE AoC)

target_include_directories(day06 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day06 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day06 PRIVATE cxx_std_20)
