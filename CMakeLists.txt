cmake_minimum_required(VERSION 3.11)
project(my_project)

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

# Include the raygui header path
include_directories(${raygui_SOURCE_DIR}/src)

# Add the executable
add_executable(my_game main.c)

# Link raylib to the project
target_link_libraries(my_game raylib)

# Set compilation flags
if (APPLE)
    target_link_libraries(my_game "-framework OpenGL" "-framework Cocoa" 
"-framework IOKit" "-framework CoreVideo")
endif()


