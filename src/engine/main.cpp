#include "raylib-cpp.hpp"
#include "../game/tank.h"
#include <string>
#include <stdio.h>
#include <dirent.h>
#include "GamePlayLoop.ixx"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

GamePlayLoop* gameLoop = nullptr;

void UpdateDrawFrame(void) {
    gameLoop->UpdateDrawFrame();
}

void list_files(const char *path) {
    // Implementation of list_files function
}

int main() {
    int screenWidth = 800;
    int screenHeight = 450;
    list_files("/resources");

    raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

    SetTargetFPS(60);

    gameLoop = new GamePlayLoop(window);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    delete gameLoop;
    return 0;
}