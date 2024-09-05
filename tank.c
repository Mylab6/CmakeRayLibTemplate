#include "tank.h"

Tank CreateTank(Vector3 position, float rotation, float scale, float size, Color color) {
    Tank tank = {
        .base = CreateGameObject(position, rotation, scale),
        .size = size,
        .color = color
    };
    return tank;
}

void DrawTank(Tank *tank) {
    float halfSize = tank->size * tank->base.scale / 2;

    // Draw cube
    DrawCube(tank->base.position, tank->size * tank->base.scale, tank->size * tank->base.scale, tank->size * tank->base.scale, tank->color);
    DrawCubeWires(tank->base.position, tank->size * tank->base.scale, tank->size * tank->base.scale, tank->size * tank->base.scale, DARKGRAY);
}