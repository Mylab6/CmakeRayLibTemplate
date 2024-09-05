#ifndef TANK_H
#define TANK_H

#include "gameObject.h"
#include "raylib.h"

typedef struct Tank {
    GameObject base;
    Color color;
    float size;
} Tank;

Tank CreateTank(Vector3 position, float rotation, float scale, float size, Color color);
void DrawTank(Tank *tank);

#endif // TANK_H