# AoC shared library
# WORKAROUND for GCC modules: Use custom commands for module compilation
# GCC requires -x c++ flag which conflicts with CMake's -MD dependency tracking

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Manually compile module files with custom commands
    # Order matters: partitions (testData, fsHelpers) before main module (result)
    set(MODULE_OBJS "")
    
    # Compile module partitions first
    foreach(MODULE_FILE testData.ixx fsHelpers.ixx)
        get_filename_component(MODULE_NAME ${MODULE_FILE} NAME_WE)
        set(MODULE_OBJ "${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}.o")
        list(APPEND MODULE_OBJS ${MODULE_OBJ})
        
        add_custom_command(
            OUTPUT ${MODULE_OBJ}
            COMMAND ${CMAKE_CXX_COMPILER}
                -I${Boost_INCLUDE_DIRS}
                -I${CMAKE_CURRENT_SOURCE_DIR}
                -g -std=c++20 -fmodules-ts
                -Wall -Wextra -Werror
                -x c++
                -c ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_FILE}
                -o ${MODULE_OBJ}
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_FILE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Compiling C++20 module partition ${MODULE_FILE}"
        )
    endforeach()
    
    # Compile main module that imports partitions
    set(RESULT_OBJ "${CMAKE_CURRENT_BINARY_DIR}/result_module.o")
    list(APPEND MODULE_OBJS ${RESULT_OBJ})
    
    add_custom_command(
        OUTPUT ${RESULT_OBJ}
        COMMAND ${CMAKE_CXX_COMPILER}
            -I${Boost_INCLUDE_DIRS}
            -I${CMAKE_CURRENT_SOURCE_DIR}
            -g -std=c++20 -fmodules-ts
            -Wall -Wextra -Werror
            -x c++
            -c ${CMAKE_CURRENT_SOURCE_DIR}/result.ixx
            -o ${RESULT_OBJ}
        DEPENDS 
            ${CMAKE_CURRENT_SOURCE_DIR}/result.ixx
            ${CMAKE_CURRENT_BINARY_DIR}/testData.o
            ${CMAKE_CURRENT_BINARY_DIR}/fsHelpers.o
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Compiling C++20 main module result.ixx"
    )
    
    # Create custom target to build all modules
    add_custom_target(AoC_modules_build DEPENDS ${MODULE_OBJS})
    
    # Compile .cpp implementation files with custom commands too
    # They need to run from build/AoC to find gcm.cache
    set(CPP_OBJS "")
    
    foreach(CPP_FILE testData.cpp result.cpp)
        get_filename_component(CPP_NAME ${CPP_FILE} NAME_WE)
        set(CPP_OBJ "${CMAKE_CURRENT_BINARY_DIR}/${CPP_NAME}_impl.o")
        list(APPEND CPP_OBJS ${CPP_OBJ})
        
        add_custom_command(
            OUTPUT ${CPP_OBJ}
            COMMAND ${CMAKE_CXX_COMPILER}
                -I${Boost_INCLUDE_DIRS}
                -I${CMAKE_CURRENT_SOURCE_DIR}
                -g -std=c++20 -fmodules-ts
                -Wall -Wextra
                -c ${CMAKE_CURRENT_SOURCE_DIR}/${CPP_FILE}
                -o ${CPP_OBJ}
            DEPENDS 
                ${CMAKE_CURRENT_SOURCE_DIR}/${CPP_FILE}
                ${RESULT_OBJ}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Compiling implementation ${CPP_FILE}"
        )
    endforeach()
    
    # Add library with manually compiled objects only
    add_library(AoC STATIC ${MODULE_OBJS} ${CPP_OBJS})
    set_target_properties(AoC PROPERTIES LINKER_LANGUAGE CXX)
    
    add_dependencies(AoC AoC_modules_build)
else()
    # For non-GCC compilers, use standard approach
    add_library(AoC STATIC
        testData.ixx
        testData.cpp
        fsHelpers.ixx
        result.ixx
        result.cpp
    )
endif()

# Include Boost
target_include_directories(AoC PUBLIC ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(AoC PUBLIC ${Boost_LIBRARIES})

# Set compile features
target_compile_features(AoC PUBLIC cxx_std_20)

# Make sure module interfaces are available to other targets
target_include_directories(AoC INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
