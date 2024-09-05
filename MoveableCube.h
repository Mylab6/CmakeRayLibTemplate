#ifndef MoveableCube_H
#define MoveableCube_H

#include "gameObject.h"
#include "raylib.h"

typedef struct MoveableCube {
    GameObject base;
    Color color;
    float size;
} MoveableCube;

MoveableCube CreateMoveableCube(Vector3 position, float rotation, float scale, float size, Color color);
void DrawMoveableCube(MoveableCube *moveableCube);

#endif // TANK_H