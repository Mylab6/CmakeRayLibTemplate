#include "basegameplayloop.h"
#include "raylib-cpp.hpp"
#include <string>
#include <stdio.h>
#include <dirent.h>
#include <vector>
#include "gameobject.h"
#include <memory>
#include <random>

using namespace std;

BaseGamePlayLoop::BaseGamePlayLoop(float screenWidth, float screenHeight, string WindowName)
    : screenWidth(screenWidth), screenHeight(screenHeight)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    window = std::make_unique<raylib::Window>(screenWidth, screenHeight, WindowName);
}

void BaseGamePlayLoop::AddGameObject(std::unique_ptr<GameObject> gameObject) {
    LoopGameObjects.push_back(std::move(gameObject));
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

    // Create a random device and random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-1.0f, 1.0f); // Generates random float values between -1 and 1

    // Create a bunch of other boxes with randomized velocities
    for(int i = 0; i < 5; i++) {
        float randomX = dis(gen);
        float randomY = dis(gen);
        float randomZ = dis(gen);
        AddGameObject(std::make_unique<GameObject>("Box#" + std::to_string(i), tankPosition, 0.0f, 6.0f, Vector3{randomX, randomY, randomZ}));
    }
}

void BaseGamePlayLoop::RunGamePlayLoop(){
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

    window->ClearBackground(BLACK);

    BeginMode3D(camera);

    DrawGrid(screenWidth, 1.0f);

    for (auto& gameObject : LoopGameObjects) {
        gameObject->Update(deltaTime);
        gameObject->DrawCubeOnGameObject();

        // Bounce logic
        if (gameObject->GetPosition().x > 10.0f || gameObject->GetPosition().x < -10.0f) {
           gameObject->ReverseVelocity();

            if(gameObject->color.b == RED.b) {
                gameObject->color = BLUE;
            }else {
                gameObject->SetColor(RED);
            }

        }
    }

    DrawCircle3D(tankPosition, 5.0f, {0.0f, 1.0f, 0.0f}, 90.0f, GREEN);

    EndMode3D();

    DrawFPS(10, 10);
    
    if (!LoopGameObjects.empty()) {
        string tankPosition = "Tank POS X " + to_string(LoopGameObjects[0]->GetPosition().x);
        DrawText(tankPosition.c_str(), 10, 40, 20, GREEN);
    }

    string gameObjectCount = "GameObject Count " + to_string(LoopGameObjects.size());
    DrawText(gameObjectCount.c_str(), 10, 50, 20, GREEN);

    EndDrawing();
}