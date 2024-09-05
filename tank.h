#ifndef TANK_H
#define TANK_H

#include "gameObject.h"

typedef struct Tank {
    GameObject base;
    float size;
} Tank;

Tank CreateTank(Vector3 position, float rotation, float scale, float size);
void DrawTank(Tank *tank, Color color);

#endif // TANK_H