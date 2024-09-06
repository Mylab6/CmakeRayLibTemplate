#include "gameobject.h"

void GameObject::Translate(const Vector3& translation) {
    position.x += translation.x;
    position.y += translation.y;
    position.z += translation.z;
}

void GameObject::Rotate(float angle) {
    rotation += angle;
}

GameObject::GameObject(const Vector3& position, float rotation, float scale)
    : position(position), rotation(rotation), scale(scale) {}