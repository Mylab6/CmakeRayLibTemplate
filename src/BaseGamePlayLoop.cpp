#include "basegameplayloop.h"
#include "raylib-cpp.hpp"
#include <string>
#include <stdio.h>
#include <dirent.h>
#include <vector>
#include "gameobject.h"
using namespace std;

BaseGamePlayLoop::BaseGamePlayLoop(float screenWidth, float screenHeight, string WindowName)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    this->window = new raylib::Window(screenWidth, screenHeight, WindowName);
    this->screenWidth = screenWidth;
  //  this-> tank =
    this->screenHeight = screenHeight;
}
void BaseGamePlayLoop::AddGameObject(GameObject gameObject) {

    LoopGameObjects.push_back(&     gameObject); 

}
void BaseGamePlayLoop::InitGame(){
    SetTargetFPS(60);
    camera = {0};
    camera.position = { 10.0f, 10.0f, 10.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    tankPosition = {0.0f, 0.0f, 0.0f};



    AddGameObject(GameObject("BlueBox" ,tankPosition, 0.0f, 3.0f,tankPosition ));
}


void BaseGamePlayLoop::RunGamePlayLoop(){
    // Update screen size if window is resized
    int newWidth = GetScreenWidth();
    int newHeight = GetScreenHeight();
    if (newWidth != screenWidth || newHeight != screenHeight) {
        screenWidth = newWidth;
        screenHeight = newHeight;
        SetMouseOffset(0, 0);
        SetMouseScale(1.0f, 1.0f);
    }

    UpdateCamera(&camera, CAMERA_ORBITAL);
    float deltaTime = GetFrameTime();

    BeginDrawing();

    this->window->ClearBackground(BLACK);

    // Begin 3D mode with the camera
    BeginMode3D(camera);

    int tankPositionX = 0 ;
    // Draw a grid
    DrawGrid(screenWidth, 1.0f);
    for(GameObject* vectorGameObject : LoopGameObjects) {
        // So their's a tank class that inherits from 
        // Game object, 
        // I want to call it's draw,
        // How best can I do that ??
        vectorGameObject->Update(deltaTime);

        vectorGameObject->DrawCubeOnGameObject();  
        tankPositionX = vectorGameObject->position.x;

        if(tankPositionX > 10.0f){
            vectorGameObject->velocity.x = -4.0f;
          //  vectorGameObject.color = RED;
        }else if(tankPositionX < -10.0f){
            vectorGameObject->velocity.x = 4.0f;
           // vectorGameObject.color = BLUE;
        }
    }

    EndMode3D();

    // Draw UI elements
    DrawFPS(10, 10);
    string tankPosition = "Tank POS X " + to_string(tankPositionX);
    DrawText(tankPosition.c_str(), 10, 40, 20, GREEN);


    string gameObjectCount  = "GameObject Count " + to_string(LoopGameObjects.size);
    DrawText(gameObjectCount.c_str(), 10, 50, 20, GREEN);

    EndDrawing();
}
