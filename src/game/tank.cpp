#include "tank.h"
#include "raylib.h"
#include "../engine/MoveableCube.h"
Tank::Tank(const Vector3& position, float rotation, float scale,  Color color, const Vector3& velocity)
    : MoveableCube(position,rotation , scale, color, velocity) {}

void Tank::Draw() {

    ::DrawCube(position, scale, scale, scale, color);
    
    // Draw cube
   // DrawCube(position, scale, scale, scale, color);
    ::DrawCubeWires(position, scale,  scale, scale, DARKGRAY);
}