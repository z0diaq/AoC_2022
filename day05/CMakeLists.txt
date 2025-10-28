# day05 executable
add_executable(day05)

target_sources(day05
    PRIVATE
        result.ixx
        result.cpp
)

target_sources(day05 PRIVATE main.cpp)

target_link_libraries(day05 PRIVATE AoC)

target_include_directories(day05 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day05 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day05 PRIVATE cxx_std_20)
