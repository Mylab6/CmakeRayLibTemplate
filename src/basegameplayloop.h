#ifndef BASEGAMEPLAYLOOP_H
#define BASEGAMEPLAYLOOP_H

#include "raylib-cpp.hpp"
#include "tank.h"
#include <string>
#include <stdio.h>
#include <dirent.h>


class BaseGamePlayLoop
{
public:
    Camera camera;
    void RunGamePlayLoop();
    void InitGame();
    BaseGamePlayLoop(float screenWidth, float screenHeight, string WindowName);
private:
    raylib::Window *window;
    Tank *tank;
    Vector3 tankPosition;
};

#endif // BASEGAMEPLAYLOOP_H
