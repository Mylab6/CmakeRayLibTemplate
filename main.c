#include "raylib.h"
#include "gui.h"
#include "math.h"
#include "rlgl.h"

int main() {
    // Initialize window and camera
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Raylib Cube Rotation");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    bool showMessageBox = false;


    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update rotation angle
        static float rotationAngle = 0.0f;
        rotationAngle += 0.5f;

        // Create transformation matrix for rotation
        #include "raylib.h" // Include the necessary header file

        Matrix rotation = { 0 }; // Initialize the rotation matrix

        // Set the rotation values
        rotation.m0 = cosf(DEG2RAD * rotationAngle);
        rotation.m1 = sinf(DEG2RAD * rotationAngle);
        rotation.m4 = -sinf(DEG2RAD * rotationAngle);
        rotation.m5 = cosf(DEG2RAD * rotationAngle);
        rotation.m10 = 1.0f;


        // Begin drawing
        BeginDrawing();
        RenderGUI(&showMessageBox);

        ClearBackground(RAYWHITE);

        // Begin 3D mode with camera
        BeginMode3D(camera);
        
        // Apply transformation matrix
        rlPushMatrix();
        rlMultMatrixf((float*)&rotation);

        // Draw cube
        DrawCube(
            (Vector3){ 0.0f, 0.0f, 0.0f }, // Position
            2.0f, 2.0f, 2.0f,              // Size
            RED                            // Color
        );

        // Draw cube wires
        DrawCubeWires(
            (Vector3){ 0.0f, 0.0f, 0.0f }, // Position
            2.0f, 2.0f, 2.0f,              // Size
            MAROON                         // Color
        );

        rlPopMatrix();

        // Draw grid (for reference)
        DrawGrid(10, 1.0f);

        // End 3D mode
        EndMode3D();

        // Draw text
        DrawText("Press ESC to exit", 10, 10, 20, GRAY);

        // End drawing
        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}