#include "basegameplayloop.h"


#include "raylib-cpp.hpp"
#include "tank.h"
#include <string>
#include <stdio.h>
#include <dirent.h>
using namespace std;

BaseGamePlayLoop::BaseGamePlayLoop(float screenWidth, float screenHeight, string WindowName)
{
    this->window = new raylib::Window (screenWidth, screenHeight, WindowName);
}
void BaseGamePlayLoop::InitGame(){
    // Initalize the camera
  //  camera =
    SetTargetFPS(60);
    camera = {0};
    camera.position = { 10.0f, 10.0f, 10.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    tankPosition = {0.0f, 0.0f, 0.0f};

    tank =  new Tank(tankPosition, 0.0f, 3.0f, BLUE);
    tank->velocity.x = 1.0f;

}

void BaseGamePlayLoop::RunGamePlayLoop(){

    // Update camera
    UpdateCamera(&camera, CAMERA_ORBITAL);
    float deltaTime = GetFrameTime();
    tank->Update(deltaTime);

    BeginDrawing();
    DrawFPS(30,30 );                                                     // Draw current FPS

    this->window->ClearBackground(BLACK);

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
    // Draw a grid
    DrawGrid(20, 1.0f);

    EndMode3D();
    string tankPosition = "Tank POS X " + to_string(tankPositionX);
    DrawText(tankPosition.c_str(), 190, 200, 20, GREEN);

    EndDrawing();
}
