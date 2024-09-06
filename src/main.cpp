#include "raylib-cpp.hpp"
#include "tank.h"
raylib::Window  window; 
Camera3D camera; 
Tank* tank = nullptr;
void UpdateDrawFrame(void);

int main() {
    int screenWidth = 800;
    int screenHeight = 450;

    raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

    SetTargetFPS(60);

    // Create a tank in the center of the screen
    Vector3 tankPosition = {0.0f, 0.0f, 0.0f};
    tank =  new Tank(tankPosition, 0.0f, 1.0f, 1.0f, RED);

    // Camera setup
    camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif
    

    return 0;
}
void UpdateDrawFrame(void){

        // Update camera
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();

        window.ClearBackground(RAYWHITE);

        // Begin 3D mode with the camera
        BeginMode3D(camera);

        // Draw the tank
        tank->Draw();

        // Draw a grid
        DrawGrid(20, 1.0f);

        EndMode3D();

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }