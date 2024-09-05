// gui.c
#include "gui.h"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "MyClass.h"
// Function to handle rendering and interactions of the GUI
void RenderGUI(bool *showMessageBox)
{
   // Adder* myAdder = Adder_create(10);
    MyClass* myClass = MyClass_Create();

    MyClass_SetValue(myClass, 42);
    int valueFromClass =  MyClass_GetValue(myClass);
    if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "#191#Show 4567 Message" + valueFromClass))
        *showMessageBox = true;

    if (*showMessageBox)
    {
        int result = GuiMessageBox((Rectangle){ 85, 70, 250, 100 },
            "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

        if (result >= 0)
            *showMessageBox = false;
    }
}
