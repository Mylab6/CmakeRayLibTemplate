#include "MoveableCube.h"
#include "raylib.h"

/// @brief 
/// @param position 
/// @param rotation 
/// @param scale 
/// @param size 
/// @param color 
MoveableCube::MoveableCube(const Vector3& position, float rotation, float scale, float size, const Color& color)
: GameObject(position, rotation, scale), size(size), color(color) {}

void MoveableCube::Draw() {
    float halfSize = size * scale / 2;

    // Draw cube
    DrawCube(position, size * scale, size * scale, size * scale, color);
    DrawCubeWires(position, size * scale, size * scale, size * scale, DARKGRAY);
}