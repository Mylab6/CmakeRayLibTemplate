// gui.c
#include "gui.h"

// Function to handle rendering and interactions of the GUI
void RenderGUI(bool *showMessageBox)
{
    if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "#191#Show Message"))
        *showMessageBox = true;

    if (*showMessageBox)
    {
        int result = GuiMessageBox((Rectangle){ 85, 70, 250, 100 },
            "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

        if (result >= 0)
            *showMessageBox = false;
    }
}
