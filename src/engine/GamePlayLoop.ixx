export module GamePlayLoop;

import <string>;
#include <raylib-cpp.hpp>
#include "../game/tank.h"
#include "gameobject.h"

export class GamePlayLoop {
public:
    GamePlayLoop(raylib::Window& window);
    void UpdateDrawFrame();

private:
    raylib::Window& window;
    Camera3D camera;
    Tank* tank;
    GameObject* prototype;

    void InitializeCamera();
    void InitializeTank();
    void InitializePrototype();
};

GamePlayLoop::GamePlayLoop(raylib::Window& win) : window(win) {
    InitializeCamera();
    InitializeTank();
    InitializePrototype();
}

void GamePlayLoop::InitializeCamera() {
    camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void GamePlayLoop::InitializeTank() {
    Vector3 tankPosition = {0.0f, 0.0f, 0.0f};
    tank = new Tank(tankPosition, 0.0f, 3.0f, BLUE);
    tank->velocity.x = 1.0f;
}

void GamePlayLoop::InitializePrototype() {
    Vector3 protoPosition = {0.0f, 0.0f, 0.0f};
    prototype = new GameObject(protoPosition, 0.0f, 3.0f);
    prototype->LoadGameModel("resources/animal-bison.obj", "resources/colormap.png");
    prototype->scale = 10;
    prototype->rotation = 180;
}

void GamePlayLoop::UpdateDrawFrame() {
    UpdateCamera(&camera, CAMERA_ORBITAL);
    float deltaTime = GetFrameTime();
    tank->Update(deltaTime);

    BeginDrawing();
    DrawFPS(30, 30);
    window.ClearBackground(BLACK);

    BeginMode3D(camera);
    
    int tankPositionX = tank->position.x;

    if (tankPositionX > 10.0f) {
        tank->velocity.x = -4.0f;
        tank->color = RED;
    } else if (tankPositionX < -10.0f) {
        tank->velocity.x = 4.0f;
        tank->color = BLUE;
    }

    tank->Draw();
    prototype->DrawGameModel();
    prototype->Update(deltaTime);
    DrawGrid(20, 1.0f);

    EndMode3D();

    std::string tankPosition = "Tank POS X " + std::to_string(tankPositionX);
    DrawText(tankPosition.c_str(), 190, 200, 20, GREEN);

    EndDrawing();
}