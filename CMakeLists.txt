cmake_minimum_required(VERSION 3.11)
project(my_project)

# Handle Emscripten (WebAssembly) build
if (EMSCRIPTEN)
    include_directories(${EMSCRIPTEN_INCLUDE_DIR})

    set(CMAKE_EXECUTABLE_SUFFIX ".wasm")
    set_target_properties(PROPERTIES COMPILE_FLAGS "-Os -s SIDE_MODULE=1 ")
    set_target_properties(PROPERTIES LINK_FLAGS "-Os -s WASM=1 -s SIDE_MODULE=1 -s STANDALONE_WASM --no-entry")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # To generate an HTML file for WebAssembly
endif ()

# Fetch raylib, raygui, and physac using FetchContent
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

include_directories(${physac_SOURCE_DIR}/src)
include_directories(${raygui_SOURCE_DIR}/src)

# Add the executable
add_executable(my_game main.c gui.c gameobject.c MoveableCube.c)

# Link raylib to the project
target_link_libraries(my_game raylib)

# Set compilation flags for different platforms
if (APPLE)
    target_link_libraries(my_game "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
elseif (ANDROID)
    message(STATUS "Compiling for Android")

    # Link against Android system libraries
    target_link_libraries(my_game log android EGL GLESv2 OpenSLES)

    # Enable GLES2 support and Android-specific flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPLATFORM_ANDROID")

    # Disable unnecessary shared libraries and examples for Android
    set(BUILD_SHARED_LIBS OFF)
    set(BUILD_EXAMPLES OFF)
    set(BUILD_GAMES OFF)

    # Ensure raylib is built for Android
    include_directories(${ANDROID_NDK}/sources/android/native_app_glue)
elseif (UNIX)
    message(STATUS "Compiling on Linux/Unix")

    # Disable Wayland support on Linux
    set(GLFW_USE_WAYLAND OFF CACHE BOOL "" FORCE)

    # Link against X11 and OpenGL
    target_link_libraries(my_game X11 GL m pthread dl)

    # Check for xkbcommon library
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(XKBCOMMON REQUIRED xkbcommon>=0.5.0)
endif()
