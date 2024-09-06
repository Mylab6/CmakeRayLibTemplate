#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib.h"
class GameObject {
public:
    Vector3 position;
    float rotation;
    float scale;

    void Translate(const Vector3& translation);
    void Rotate(float angle);

    GameObject(const Vector3& position, float rotation, float scale);
};

#endif // GAMEOBJECT_H