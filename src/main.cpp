#include "basegameplayloop.h"
#include "raylib-cpp.hpp"
#include "tank.h"
#include <string>
#include <stdio.h>
#include <dirent.h> 
using namespace std;

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif
//raylib::Window  window; 
//Camera3D camera; 
//Tank* tank = nullptr;
//GameObject* prototype = nullptr; 
void UpdateDrawFrame(void);
void list_files(const char *path);
BaseGamePlayLoop* gamePlayLoop ;
int main() {

   // list_files("/resources");
    int screenWidth = 300;
    int screenHeight = 300;
    //raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");
    gamePlayLoop = new BaseGamePlayLoop(screenHeight,screenWidth,"GamePlayLoop");


  //  SetTargetFPS(60);

    // Create a tank in the center of the screen

    // Camera setup
    gamePlayLoop->InitGame();
    /*
    prototype = new GameObject(tankPosition, 0.0f, 3.0f);
    //prototype->LoadGameModel("/resources/animal-bison.obj", "/resources/KennyAssets/Prototype/Models/OBJ format/Textures/colormap.png");

    prototype->LoadGameModel("resources/animal-bison.obj", "resources/colormap.png");
    //    prototype->LoadGameModel("animal-bison.obj", "colormap.png");

    prototype->scale = 10;  
    prototype->rotation = 180; */
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

    gamePlayLoop->RunGamePlayLoop();
    }



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
