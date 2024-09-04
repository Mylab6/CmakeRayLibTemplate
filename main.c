// main.c
#include "raylib.h"
#include "gui.h"
#include "rlgl.h"

int main()
{
    const int screenWidth = 1080; 
    const int screenHeight = 720 ; 
    InitWindow(screenWidth/2, screenHeight/2, "raygui - 45678 test suite");
    SetTargetFPS(60);
 // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    bool showMessageBox = false;
    float time = 0.0f; 
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        Vector2 centre = {(float)screenWidth/2 , (float)screenHeight/2};
        // Call the GUI rendering function
        RenderGUI(&showMessageBox);
        
            BeginMode3D(camera);
                //rlTranslatef(centre.x, centre.y, 0 );
                //rlRotatef(time * 50, 0, 0,-1); 
                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

                DrawGrid(10, 1.0f);

            EndMode3D();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
