#include "tank.h"
#include "raylib.h"
#include "MoveableCube.h"
Tank::Tank(const Vector3& position, float rotation, float scale,  Color color, const Vector3& velocity)
    : MoveableCube(position,rotation , scale, color, velocity) {}

void Tank::Draw() {

    MoveableCube::Draw();
}