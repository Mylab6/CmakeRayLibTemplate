#include "gameobject.h"
#include "raylib-cpp.hpp"
#include "raylib.h"

void GameObject::Translate( Vector3 translation) {
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
void GameObject::DrawCubeOnGameObject() {
    
    // Draw cube
    std::cout << "Drawing a Cube" << std::endl;

    DrawCube(position, scale, scale, scale, BLUE);
    DrawCubeWires(position, scale, scale, scale, DARKGRAY);
}
void GameObject::Draw() {
    std::cout << "Drawing a circle" << std::endl;
}

GameObject::GameObject(string name,  Vector3 position, float rotation, float scale,Vector3 velocity)
    :  position(position), rotation(rotation), scale(scale) ,velocity(velocity) {}