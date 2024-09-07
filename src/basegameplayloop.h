#ifndef BASEGAMEPLAYLOOP_H
#define BASEGAMEPLAYLOOP_H
#include "raylib.h"


class BaseGamePlayLoop
{
public:
    Camera camera;
    BaseGamePlayLoop();
    void InitGame();
    void RunGamePlayLoop();
};

#endif // BASEGAMEPLAYLOOP_H
