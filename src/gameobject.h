#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib-cpp.hpp"
#include "raylib.h"
#include <string>

class GameObject {
public:
    GameObject(const std::string& name, const Vector3& position, float rotation, float scale, const Vector3& velocity = {0.0f, 0.0f, 0.0f});

    void Translate(const Vector3& translation);
    void Rotate(float angle);
    void Update(float deltaTime);
    void LoadGameModel(const std::string& modelPath, const std::string& texturePath);
    void DrawGameModel() const;
    void DrawCubeOnGameObject() const;
    virtual void Draw() const;

    void SetColor(Color color);
    Color color = WHITE;


    // Getter methods (you might want to add these)
    const std::string& GetName() const { return name; }
    const Vector3& GetPosition() const { return position; }
    float GetRotation() const { return rotation; }
    float GetScale() const { return scale; }
    const Vector3& GetVelocity() const { return velocity; }

    // Setter methods (if needed)
    void SetVelocity(const Vector3& newVelocity) { velocity = newVelocity; }

protected:
    std::string name;
    Vector3 position;
    float rotation;
    float scale;
    Vector3 velocity;
    Model model;
    Texture2D texture;
};

#endif // GAMEOBJECT_H