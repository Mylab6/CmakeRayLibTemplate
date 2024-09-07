#include "gameobject.h"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <iostream>

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
void GameObject::ReverseVelocity() {
    velocity.x = -velocity.x;
    velocity.y = -velocity.y;
    velocity.z = -velocity.z;

}
void GameObject::LoadGameModel(const std::string& modelPath, const std::string& texturePath) {
    model = LoadModel(modelPath.c_str());
    texture = LoadTexture(texturePath.c_str());
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}

void GameObject::DrawGameModel() const {
    DrawModel(model, position, scale, color);
}

void GameObject::DrawCubeOnGameObject() const {
    std::cout << "Drawing a Cube" << std::endl;
    std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
    std::cout << "Scale: " << scale << std::endl;

    DrawCube(position, scale, scale, scale, color);
    DrawCubeWires(position, scale, scale, scale, DARKGRAY);
}

void GameObject::Draw() const {
    std::cout << "Drawing a circle" << std::endl;
}

void GameObject::SetColor(Color color) {
this->color = color;
}
GameObject::GameObject(const std::string& name, const Vector3& position, float rotation, float scale, const Vector3& velocity)
    : name(name), position(position), rotation(rotation), scale(scale), velocity(velocity) {}