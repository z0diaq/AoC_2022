# day01 executable
# WORKAROUND for GCC modules: Use custom command for module compilation

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Manually compile day01 module with custom command
    set(DAY01_MODULE_OBJ "${CMAKE_CURRENT_BINARY_DIR}/result.o")
    
    add_custom_command(
        OUTPUT ${DAY01_MODULE_OBJ}
        COMMAND ${CMAKE_CXX_COMPILER}
            -I${Boost_INCLUDE_DIRS}
            -I${CMAKE_SOURCE_DIR}/AoC
            -I${CMAKE_CURRENT_SOURCE_DIR}
            -g -std=c++20 -fmodules-ts
            -Wall -Wextra -Werror
            -x c++
            -c ${CMAKE_CURRENT_SOURCE_DIR}/result.ixx
            -o ${DAY01_MODULE_OBJ}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/result.ixx AoC
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Compiling C++20 module result.ixx for day01"
    )
    
    add_custom_target(day01_module_build DEPENDS ${DAY01_MODULE_OBJ})
    
    # Compile main.cpp with custom command from build directory to find gcm.cache
    set(DAY01_MAIN_OBJ "${CMAKE_CURRENT_BINARY_DIR}/main.o")
    
    add_custom_command(
        OUTPUT ${DAY01_MAIN_OBJ}
        COMMAND ${CMAKE_CXX_COMPILER}
            -I${Boost_INCLUDE_DIRS}
            -I${CMAKE_SOURCE_DIR}/AoC
            -I${CMAKE_CURRENT_SOURCE_DIR}
            -g -std=c++20 -fmodules-ts
            -Wall -Wextra -Werror
            -c ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
            -o ${DAY01_MAIN_OBJ}
        DEPENDS 
            ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
            ${DAY01_MODULE_OBJ}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build/AoC
        COMMENT "Compiling main.cpp for day01"
    )
    
    # Create executable with manually compiled objects
    add_executable(day01 ${DAY01_MAIN_OBJ} ${DAY01_MODULE_OBJ})
    set_target_properties(day01 PROPERTIES LINKER_LANGUAGE CXX)
    
    add_dependencies(day01 day01_module_build AoC)
else()
    # For non-GCC compilers
    add_executable(day01
        result.ixx
        main.cpp
    )
endif()

# Link against AoC library (module dependency)
target_link_libraries(day01 PRIVATE AoC)

target_include_directories(day01 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(day01 PRIVATE ${Boost_LIBRARIES})

target_compile_features(day01 PRIVATE cxx_std_20)
