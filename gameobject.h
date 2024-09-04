#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib.h"

typedef struct GameObject {
    Vector2 position;
    float rotation;
    float scale;
    void (*Translate)(struct GameObject*, Vector2);
    void (*Rotate)(struct GameObject*, float);
} GameObject;

GameObject CreateGameObject(Vector2 position, float rotation, float scale);
void TranslateGameObject(GameObject *obj, Vector2 translation);
void RotateGameObject(GameObject *obj, float angle);

#endif // GAMEOBJECT_H