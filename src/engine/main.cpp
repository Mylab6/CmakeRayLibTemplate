#include "raylib-cpp.hpp"
#include "../game/tank.h"
#include <string>
#include <stdio.h>
#include <dirent.h> 
using namespace std;

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif
raylib::Window  window; 
Camera3D camera; 
Tank* tank = nullptr;
GameObject* prototype = nullptr; 
void UpdateDrawFrame(void);
void list_files(const char *path);

int main() {
    int screenWidth = 800;
    int screenHeight = 450;
    list_files("/resources");

    raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

    SetTargetFPS(60);

    // Create a tank in the center of the screen
    Vector3 tankPosition = {0.0f, 0.0f, 0.0f};
    
    tank =  new Tank(tankPosition, 0.0f, 3.0f, BLUE);
    tank->velocity.x = 1.0f;
    // Camera setup
    camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    prototype = new GameObject(tankPosition, 0.0f, 3.0f);
    //prototype->LoadGameModel("/resources/animal-bison.obj", "/resources/KennyAssets/Prototype/Models/OBJ format/Textures/colormap.png");
    
    prototype->LoadGameModel("resources/animal-bison.obj", "resources/colormap.png");
    //    prototype->LoadGameModel("animal-bison.obj", "colormap.png");

    prototype->scale = 10;  
    prototype->rotation = 180; 
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
        float deltaTime = GetFrameTime();
        tank->Update(deltaTime);

        BeginDrawing();
        DrawFPS(30,30 );                                                     // Draw current FPS

        window.ClearBackground(BLACK);

        // Begin 3D mode with the camera
        BeginMode3D(camera);
        int tankPositionX = tank->position.x;

        if(tankPositionX > 10.0f){
            tank->velocity.x = -4.0f;
            tank->color = RED;
        }else if( tankPositionX< -10.0f){
            tank->velocity.x = 4.0f;
            tank->color = BLUE;
        }
        // Draw the tank
        tank->Draw();
       prototype->DrawGameModel();
        prototype->Update(deltaTime);
        // Draw a grid
        DrawGrid(20, 1.0f);

        EndMode3D();
        string tankPosition = "Tank POS X " + to_string(tankPositionX);
        DrawText(tankPosition.c_str(), 190, 200, 20, GREEN);

        EndDrawing();
    }


// Just  a debug function, troubleshooting the file path issue
// Happens with web builds
void list_files(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        printf("Could not open directory: %s\n", path);
        return;
    }

    printf("Listing files in directory: %s\n", path);
    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dp);
}