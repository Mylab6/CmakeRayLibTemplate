#include "tank.h"

Tank CreateTank(Vector3 position, float rotation, float scale, float size) {
    Tank tank = {
        .base = CreateGameObject(position, rotation, scale),
        .size = size
    };
    return tank;
}

void DrawTank(Tank *tank, Color color) {
    Vector3  tankVector =        {tank->base.position.x, tank->base.position.y, tank->base.position.z}; 

    DrawCube(
        tankVector,
        10, tank->size * tank->base.scale, 10,color
    );
}