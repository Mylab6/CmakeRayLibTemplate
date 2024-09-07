#ifndef BASEGAMEPLAYLOOP_H
#define BASEGAMEPLAYLOOP_H

#include "raylib-cpp.hpp"
#include <string>
#include <stdio.h>
#include <dirent.h>
#include "gameobject.h"

#include <vector>


class BaseGamePlayLoop
{
public:
    Camera camera;
    void RunGamePlayLoop();
    void InitGame();
    std::vector<GameObject*> LoopGameObjects;

    BaseGamePlayLoop(float screenWidth, float screenHeight, string WindowName);
    void AddGameObject(GameObject gameObject);
private:
    raylib::Window *window;
   // Tank tank;
    Vector3 tankPosition;
    int screenWidth;
    int screenHeight;
};

#endif // BASEGAMEPLAYLOOP_H
