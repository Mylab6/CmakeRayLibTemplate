#include "raylib.h"
#include "gui.h"
#include "math.h"
#include "rlgl.h"
#include "tank.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib Tank Example");

    Tank player = CreateTank((Vector3){screenWidth / 2, screenHeight / 2, 0.0f}, 0.0f, 1.0f, 40.0f);

    // Define the camera to look into our 3D world
    Camera camera = { 0 };
    camera.position = (Vector3){ 5.0f, 4.0f, 5.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
    bool showMessageBox = false;

    while (!WindowShouldClose()) {
        RenderGUI(&showMessageBox);

        // Example input handling for translation and rotation
        Vector3 translation = {0.0f, 0.0f, 0.0f};
        float rotation = 0.0f;

        if (IsKeyDown(KEY_RIGHT)) translation.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) translation.x -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) translation.y += 2.0f;
        if (IsKeyDown(KEY_UP)) translation.y -= 2.0f;
        if (IsKeyDown(KEY_A)) rotation += 1.0f;
        if (IsKeyDown(KEY_D)) rotation -= 1.0f;

        player.base.Translate(&player.base, translation);
        player.base.Rotate(&player.base, rotation);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        // Draw player
        DrawTank(&player, GREEN);
        EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}