#include "tank.h"
#include "raylib.h"
#include "MoveableCube.h"
Tank::Tank(const Vector3& position, float rotation, float scale, float size, const Color& color)
    : MoveableCube(position, rotation, scale, size, color) {}

void Tank::Draw() {
    float halfSize = size * scale / 2;
    DrawCube(position, size * scale, size * scale, size * scale, color);
    // Draw cube
   // DrawCube(position, size * scale, size * base.scale, size * base.scale, color);
   // DrawCubeWires(base.position, size * base.scale, size * base.scale, size * base.scale, DARKGRAY);
}