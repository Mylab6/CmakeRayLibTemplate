#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib.h"
class GameObject {
public:
    Vector3 position;
    float rotation;
    float scale;
    Vector3 velocity;  // New field

    void Translate(const Vector3& translation);
    void Rotate(float angle);
    void Update(float deltaTime);  // New method to update position based on velocity

    GameObject(const Vector3& position, float rotation, float scale, const Vector3& velocity = {0.0f, 0.0f, 0.0f});
};

#endif // GAMEOBJECT_H