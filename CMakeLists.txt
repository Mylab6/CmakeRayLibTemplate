cmake_minimum_required(VERSION 3.20)
project(my_project C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Emscripten configuration
if(EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set(EMSCRIPTEN_FLAGS "-s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EMSCRIPTEN_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EMSCRIPTEN_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s SIDE_MODULE=1 -s STANDALONE_WASM --no-entry")
endif()

# GLFW configuration for Unix systems
if(UNIX AND NOT APPLE AND NOT EMSCRIPTEN)
  set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "Build Wayland backend")
  set(GLFW_BUILD_X11 ON CACHE BOOL "Build X11 backend")
endif()

# Fetch external dependencies
include(FetchContent)

# Declare dependencies
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG master
)

FetchContent_Declare(
  raygui
  GIT_REPOSITORY https://github.com/raysan5/raygui.git
  GIT_TAG master
)

FetchContent_Declare(
  physac
  GIT_REPOSITORY https://github.com/victorfisac/Physac.git
  GIT_TAG master
)

FetchContent_Declare(
  raylib_cpp
  GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
  GIT_TAG v5.0.2
)

# Make dependencies available
FetchContent_MakeAvailable(raylib raygui physac raylib_cpp)

# Include directories
include_directories(
  ${physac_SOURCE_DIR}/src
  ${raygui_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/resources
)

# Gather source files
file(GLOB_RECURSE SRC_FILES
  "${CMAKE_SOURCE_DIR}/src/*.c"
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Add executable
add_executable(index ${SRC_FILES})

# Link libraries
target_link_libraries(index PRIVATE raylib raylib_cpp)

if(APPLE)
  target_link_libraries(index PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
elseif(UNIX AND NOT APPLE AND NOT EMSCRIPTEN)
  find_package(PkgConfig REQUIRED)
  # Uncomment the following line if you need xkbcommon
  # pkg_check_modules(XKBCOMMON REQUIRED xkbcommon>=0.5.0)
endif()

# Emscripten-specific link options
if(EMSCRIPTEN)
  target_link_options(index PRIVATE
    -Os
    -s WASM=1
    --preload-file ${CMAKE_SOURCE_DIR}/resources@/resources
  )
endif()

# Set properties for all configurations
set_target_properties(index PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Add compile definitions for debug builds
target_compile_definitions(index PRIVATE $<$<CONFIG:Debug>:DEBUG>)

# Enable warnings and treat them as errors
#if(MSVC)
#  target_compile_options(index PRIVATE /W4 /WX)
#else()
#  target_compile_options(index PRIVATE -Wall -Wextra -Wpedantic -Werror)
#endif()
