#include "gameobject.h"

void GameObject::Translate(const Vector3& translation) {
    position.x += translation.x;
    position.y += translation.y;
    position.z += translation.z;
}

void GameObject::Rotate(float angle) {
    rotation += angle;
}
void GameObject::Update(float deltaTime) {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    position.z += velocity.z * deltaTime;
}

GameObject::GameObject(const Vector3& position, float rotation, float scale, const Vector3& velocity)
    : position(position), rotation(rotation), scale(scale) ,velocity(velocity) {}