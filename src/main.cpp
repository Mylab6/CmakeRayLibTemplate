#include "raylib-cpp.hpp"
#include "tank.h"

int main() {
    int screenWidth = 800;
    int screenHeight = 450;

    raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

    SetTargetFPS(60);

    // Create a tank in the center of the screen
    Vector3 tankPosition = {0.0f, 0.0f, 0.0f};
    Tank tank(tankPosition, 0.0f, 1.0f, 1.0f, RED);

    // Camera setup
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while (!window.ShouldClose()) {
        // Update camera
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();

        window.ClearBackground(RAYWHITE);

        // Begin 3D mode with the camera
        BeginMode3D(camera);

        // Draw the tank
        tank.Draw();

        // Draw a grid
        DrawGrid(20, 1.0f);

        EndMode3D();

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    return 0;
}