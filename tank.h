#ifndef TANK_H
#define TANK_H

#include "gameObject.h"

typedef struct Tank {
    GameObject base;
    float size;
} Tank;

Tank CreateTank(Vector2 position, float rotation, float scale, float size);
void DrawTank(Tank *tank);

#endif // TANK_H