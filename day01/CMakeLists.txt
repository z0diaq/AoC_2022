# day01 executable
add_executable(day01)

target_sources(day01
    PRIVATE
        result.ixx
)

target_sources(day01 PRIVATE main.cpp)

target_link_libraries(day01 PRIVATE AoC)

target_include_directories(day01 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day01 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day01 PRIVATE cxx_std_20)
