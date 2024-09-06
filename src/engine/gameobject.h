#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>

#include "raylib-cpp.hpp"
#include <string>
#include "raylib.h"

using namespace std;

class GameObject {
public:
    Vector3 position;
    float rotation;
    float scale;
    Vector3 velocity;  // New field
    void Translate(const Vector3& translation);
    void Rotate(float angle);
    void Update(float deltaTime);  // New method to update position based on velocity

    void LoadGameModel(string modelPath, string texturePath);

    void LoadGameModel();

    Model model ;
    bool modelLoaded = false;
    Texture2D texture ;
    //model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;   
    void DrawGameModel();

    GameObject(const Vector3& position, float rotation, float scale, const Vector3& velocity = {0.0f, 0.0f, 0.0f});
};

#endif // GAMEOBJECT_H