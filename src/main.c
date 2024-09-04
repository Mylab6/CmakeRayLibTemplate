// main.c
#include "raylib.h"
#include "gui.h"

int main()
{
    InitWindow(400, 200, "raygui - controls test suite");
    SetTargetFPS(60);

    bool showMessageBox = false;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        // Call the GUI rendering function
        RenderGUI(&showMessageBox);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
