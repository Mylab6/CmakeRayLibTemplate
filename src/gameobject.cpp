#include "gameobject.h"
#include "raylib-cpp.hpp"
#include <iostream>
#include "raylib.h"

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
void GameObject::LoadGameModel(string modelPath , string texturePath) {
     model = LoadModel(modelPath.c_str());                 // Load OBJ model
    texture = LoadTexture(texturePath.c_str());    // Load model texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;   // Set model diffuse texture
   // modelLoaded = true;
}
void GameObject::DrawGameModel() {
    
    DrawModel(model, position, scale, WHITE);        // Draw 3d model with texture


}


GameObject::GameObject(const Vector3& position, float rotation, float scale, const Vector3& velocity)
    : position(position), rotation(rotation), scale(scale) ,velocity(velocity) {}