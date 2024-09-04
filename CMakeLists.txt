cmake_minimum_required(VERSION 3.11)
project(my_project)

if (EMSCRIPTEN)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
  set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so taht you can directly open it.
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

FetchContent_Declare(
  physac
  GIT_REPOSITORY https://github.com/victorfisac/Physac.git
  GIT_TAG        master # You can specify a particular tag, branch, or commit
)

# Fetch Physac
FetchContent_MakeAvailable(physac)

include_directories(${physac_SOURCE_DIR}/src)

# Include the raygui header path
include_directories(${raygui_SOURCE_DIR}/src)

# Add the executable
add_executable(my_game main.c  gui.c, gameobject.c)

# Link raylib to the project
target_link_libraries(my_game raylib)


# Set compilation flags
if (APPLE)
    target_link_libraries(my_game "-framework OpenGL" "-framework Cocoa" 
"-framework IOKit" "-framework CoreVideo")
else()
if (UNIX)
# On Linux, disable Wayland and ensure xkbcommon is available
  message(STATUS "Compiling on Linux/Unix")

# Disable Wayland support
  set(GLFW_USE_WAYLAND OFF CACHE BOOL "" FORCE)

# Check for xkbcommon library
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(XKBCOMMON REQUIRED xkbcommon>=0.5.0)

endif()
endif()

