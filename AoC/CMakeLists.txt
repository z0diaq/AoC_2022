# AoC shared library
add_library(AoC STATIC)

# Add all sources - treat .ixx files as regular sources for GCC compatibility
target_sources(AoC
    PRIVATE
        testData.ixx
        testData.cpp
        fsHelpers.ixx
        result.ixx
        result.cpp
)

# Include Boost
target_include_directories(AoC PUBLIC ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(AoC PUBLIC ${Boost_LIBRARIES})

# Set compile features
target_compile_features(AoC PUBLIC cxx_std_20)

# Make sure module interfaces are available to other targets
target_include_directories(AoC INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
