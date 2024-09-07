#include "basegameplayloop.h"
#include "raylib-cpp.hpp"
#include "tank.h"
#include <string>
#include <stdio.h>
#include <dirent.h>
using namespace std;

BaseGamePlayLoop::BaseGamePlayLoop(float screenWidth, float screenHeight, string WindowName)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    this->window = new raylib::Window(screenWidth, screenHeight, WindowName);
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
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

    tank = new Tank(tankPosition, 0.0f, 3.0f, BLUE);
    tank->velocity.x = 1.0f;
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
    tank->Update(deltaTime);

    BeginDrawing();

    this->window->ClearBackground(GREEN             );

    // Begin 3D mode with the camera
    BeginMode3D(camera);
    int tankPositionX = tank->position.x;

    if(tankPositionX > 10.0f){
        tank->velocity.x = -4.0f;
        tank->color = RED;
    }else if(tankPositionX < -10.0f){
        tank->velocity.x = 4.0f;
        tank->color = BLUE;
    }

    // Draw a grid
    DrawGrid(screenWidth, 1.0f);
    tank->Draw();
    EndMode3D();

    // Draw UI elements
    DrawFPS(10, 10);
    string tankPosition = "Tank POS X " + to_string(tankPositionX);
    DrawText(tankPosition.c_str(), 10, 40, 20, GREEN);

    EndDrawing();
}