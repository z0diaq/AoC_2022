# day02 executable
add_executable(day02)

target_sources(day02
    PRIVATE
        result.ixx
        result.cpp
)

target_sources(day02 PRIVATE main.cpp)

target_link_libraries(day02 PRIVATE AoC)

target_include_directories(day02 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day02 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day02 PRIVATE cxx_std_20)
