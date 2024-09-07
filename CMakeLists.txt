cmake_minimum_required(VERSION 3.20)
project(my_project C CXX)

# Ensure C++20 is enabled
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable experimental C++20 modules support for GCC
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")
endif()

# EMSCRIPTEN-specific configuration
if (EMSCRIPTEN)
    include_directories(${EMSCRIPTEN_INCLUDE_DIR})
    set(CMAKE_EXECUTABLE_SUFFIX ".wasm")

    set_target_properties(index PROPERTIES COMPILE_FLAGS "-Os -s SIDE_MODULE=1 --preload-file ${CMAKE_SOURCE_DIR}/resources")
    set_target_properties(index PROPERTIES LINK_FLAGS "-Os -s WASM=1 --preload-file ${CMAKE_SOURCE_DIR}/resources -s SIDE_MODULE=1 -s STANDALONE_WASM --no-entry")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 --preload-file ${CMAKE_SOURCE_DIR}/resources -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

# Fetch raylib and raygui via FetchContent
include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
  raygui
  GIT_REPOSITORY https://github.com/raysan5/raygui.git
  GIT_TAG master
)
FetchContent_MakeAvailable(raygui)

# Fetch Physac
FetchContent_Declare(
  physac
  GIT_REPOSITORY https://github.com/victorfisac/Physac.git
  GIT_TAG master
)
FetchContent_MakeAvailable(physac)

# Fetch raylib_cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION v5.0.2)
    endif()
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

# Include necessary directories
include_directories(${physac_SOURCE_DIR}/src)
include_directories(${raygui_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/resources)
include_directories(engine game)

# Find all source files
file(GLOB_RECURSE SRC_FILES 
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.ixx"
)

# Create the executable
add_executable(index ${SRC_FILES})

# Link libraries
target_link_libraries(index PRIVATE raylib raylib_cpp stdc++)

# EMSCRIPTEN-specific options
if (EMSCRIPTEN)
  target_link_options(index PRIVATE
    -Os
    "-s WASM=1"
    --preload-file ${CMAKE_SOURCE_DIR}/resources@/resources
  )
endif()

# Platform-specific settings
if (APPLE)
    target_link_libraries(index "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
elseif (UNIX)
    message(STATUS "Compiling on Linux/Unix")
    # Disable Wayland support
    set(GLFW_USE_WAYLAND OFF CACHE BOOL "" FORCE)
endif()

# Set module properties for .ixx files
set_source_files_properties(${SRC_FILES} PROPERTIES
    LANGUAGE CXX
    COMPILE_FLAGS "-fmodules-ts"
)

# Ensure the project is built with C++20 support
target_compile_features(index PRIVATE cxx_std_20)

# Print information about the files being compiled
foreach(SOURCE_FILE ${SRC_FILES})
    message(STATUS "Compiling: ${SOURCE_FILE}")
endforeach()