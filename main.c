#include "raylib.h"
#include "MoveableCube.h"

#define NUM_TANKS 4

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Initialize tanks
    MoveableCube tanks[NUM_TANKS] = {
        CreateMoveableCube((Vector3){ 0.0f, 0.0f, 0.0f }, 0.0f, 1.0f, 1.0f, BLUE), 
        CreateMoveableCube((Vector3){ 2.0f, 0.0f, 0.0f }, 0.0f, 1.0f, 1.0f, RED),
        CreateMoveableCube((Vector3){ -2.0f, 0.0f, 0.0f }, 0.0f, 1.0f, 1.0f, GREEN),
        CreateMoveableCube((Vector3){ 0.0f, 0.0f, 0.0f }, 0.0f, 1.0f, 1.0f, PINK), 

    };

    // Set tank colors

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyPressed('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };

        // Update tank positions and rotations
        static float moveSpeed = 0.05f;
        static float turnSpeed = 1.0f;

        for (int i = 0; i < NUM_TANKS; i++) {
            tanks[i].base.Translate(&tanks[i].base, (Vector3){ 0.0f, 0.0f, moveSpeed });
            if (tanks[i].base.position.z > 5.0f || tanks[i].base.position.z < -5.0f) {
                tanks[i].base.Rotate(&tanks[i].base, 180.0f);
                moveSpeed = -moveSpeed;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                for (int i = 0; i < NUM_TANKS; i++) {
                    DrawMoveableCube(&tanks[i]);
                }

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawRectangle( 10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 93, BLUE);

            DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
            DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}