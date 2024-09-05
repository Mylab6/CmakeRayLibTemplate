#include "raylib.h"
#include "MoveableCube.h"
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif
#define NUM_TANKS 4
#include "gui.h"
#include "MyClass.h"
#include <string.h>
// Declare global variables for Web compatibility
Camera3D camera;
MoveableCube tanks[NUM_TANKS];
int valueFromClass;
char str[256];  // Create a buffer to hold the resulting string

bool showMessage ;
// Forward declaration of UpdateDrawFrame
void UpdateDrawFrame(void);
MyClass* myClass;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    myClass = MyClass_Create();

    MyClass_SetValue(myClass, 42);
   
 

    strcpy(str, MyClass_GetString(myClass));


    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Initialize tanks
    tanks[0] = CreateMoveableCube((Vector3){ 0.0f, 0.0f, 0.0f }, 0.0f, 1.0f, 1.0f, BLUE);
    tanks[1] = CreateMoveableCube((Vector3){ 2.0f, 0.0f, 0.0f }, 0.0f, 1.0f, 1.0f, RED);
    tanks[2] = CreateMoveableCube((Vector3){ -2.0f, 0.0f, 0.0f }, 0.0f, 1.0f, 1.0f, GREEN);
    tanks[3] = CreateMoveableCube((Vector3){ 3.0f, 0.0f, 0.0f }, 0.0f, 1.0f, 1.0f, PINK);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Update and Draw function (global camera and tanks used)
void UpdateDrawFrame(void)
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
        //RenderGUI(&showMessage); 
        DrawText(str, 20, 20, 10, BLACK);
        DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
        DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
