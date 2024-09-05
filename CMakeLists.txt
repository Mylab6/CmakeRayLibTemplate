cmake_minimum_required(VERSION 3.11)
project(my_project)

# Check for Emscripten environment and set appropriate flags
if (EMSCRIPTEN)
    include_directories(${EMSCRIPTEN_INCLUDE_DIR})

    set(CMAKE_EXECUTABLE_SUFFIX ".wasm")

    set_target_properties(my_game PROPERTIES COMPILE_FLAGS "-Os -s SIDE_MODULE=1")
    set_target_properties(my_game PROPERTIES LINK_FLAGS "-Os -s WASM=1 -s SIDE_MODULE=1 -s STANDALONE_WASM --no-entry")
    
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")  # Set to build with Emscripten HTML template
endif ()

# Fetch raylib and raygui via FetchContent
include(FetchContent)

# Fetch raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

# Fetch raygui
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

# Include the necessary directories
include_directories(${physac_SOURCE_DIR}/src)
include_directories(${raygui_SOURCE_DIR}/src)

# Recursively find all .c and .cpp files in the src directory
file(GLOB_RECURSE SRC_FILES_C "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE SRC_FILES_CPP "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Combine .c and .cpp files into one list
set(SRC_FILES ${SRC_FILES_C} ${SRC_FILES_CPP})

# Add the executable using all source files found
add_executable(my_game ${SRC_FILES})

# Link raylib to the project
target_link_libraries(my_game raylib)

# Set compilation flags for different platforms
if (APPLE)
    target_link_libraries(my_game "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
elseif(UNIX)
    # On Linux, disable Wayland and ensure xkbcommon is available
    message(STATUS "Compiling on Linux/Unix")

    # Disable Wayland support
    set(GLFW_USE_WAYLAND OFF CACHE BOOL "" FORCE)

    # Check for xkbcommon library
    find_package(PkgConfig REQUIRED)
    #pkg_check_modules(XKBCOMMON REQUIRED xkbcommon>=0.5.0)
endif()
