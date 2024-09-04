#include "tank.h"

Tank CreateTank(Vector2 position, float rotation, float scale, float size) {
    Tank tank = {
        .base = CreateGameObject(position, rotation, scale),
        .size = size
    };
    return tank;
}

void DrawTank(Tank *tank) {
    DrawRectanglePro(
        (Rectangle){tank->base.position.x, tank->base.position.y, tank->size * tank->base.scale, tank->size * tank->base.scale},
        (Vector2){tank->size * tank->base.scale / 2, tank->size * tank->base.scale / 2},
        tank->base.rotation,
        MAROON
    );
}