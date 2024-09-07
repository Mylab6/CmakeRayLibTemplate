cmake_minimum_required(VERSION 3.20)
project(my_project C CXX)

# Ensure C++20 is enabled
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable C++20 modules support for GCC
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")
endif()

# Include the module configuration
include(cmake/ModuleConfig.cmake)

# ... [Keep the rest of your existing CMake configuration for external libraries] ...

# Find all source files (excluding main.cpp)
file(GLOB_RECURSE SRC_FILES 
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/src/engine/main.cpp")

# Create a library from the source files
add_library(project_lib STATIC ${SRC_FILES})
target_compile_options(project_lib PRIVATE -fmodules-ts -fprebuilt-module-path=${CMAKE_BINARY_DIR}/gcm.cache)
add_dependencies(project_lib build_modules)

# Create the executable
add_executable(index "${CMAKE_SOURCE_DIR}/src/engine/main.cpp")
target_compile_options(index PRIVATE -fmodules-ts -fprebuilt-module-path=${CMAKE_BINARY_DIR}/gcm.cache)
target_link_libraries(index PRIVATE project_lib)

# ... [Keep the rest of your existing CMake configuration] ...

# Ensure the project is built with C++20 support
target_compile_features(index PRIVATE cxx_std_20)

# Print information about the files being compiled
message(STATUS "Source files:")
foreach(SOURCE_FILE ${SRC_FILES})
    message(STATUS "  ${SOURCE_FILE}")
endforeach()

message(STATUS "Module files:")
foreach(MODULE_FILE ${MODULE_FILES})
    message(STATUS "  ${MODULE_FILE}")
endforeach()