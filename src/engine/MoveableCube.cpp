#include "MoveableCube.h"
#include "raylib.h"

MoveableCube::MoveableCube(const Vector3& position, float rotation, float scale,  Color color,const Vector3& velocity)
: GameObject(position, rotation, scale,  velocity) {

    this->color = color;
}



void MoveableCube::Draw() {
    
    // Draw cube
    DrawCube(position, scale, scale, scale, color);
    DrawCubeWires(position, scale, scale, scale, DARKGRAY);
}