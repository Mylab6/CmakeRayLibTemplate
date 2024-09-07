#ifndef BASEGAMEPLAYLOOP_H
#define BASEGAMEPLAYLOOP_H

#include "raylib-cpp.hpp"
#include "gameobject.h"
#include <string>
#include <vector>
#include <memory>

class BaseGamePlayLoop {
public:
    BaseGamePlayLoop(float screenWidth, float screenHeight, std::string WindowName);
    void AddGameObject(std::unique_ptr<GameObject> gameObject);
    void InitGame();
    void RunGamePlayLoop();

private:
    std::unique_ptr<raylib::Window> window;
    float screenWidth;
    float screenHeight;
    Camera3D camera;
    Vector3 tankPosition;
    std::vector<std::unique_ptr<GameObject>> LoopGameObjects;
};

#endif // BASEGAMEPLAYLOOP_H