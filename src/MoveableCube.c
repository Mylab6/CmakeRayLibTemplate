#include "MoveableCube.h"

MoveableCube CreateMoveableCube(Vector3 position, float rotation, float scale, float size, Color color) {
    MoveableCube moveableCube = {
        .base = CreateGameObject(position, rotation, scale),
        .size = size,
        .color = color
    };
    return moveableCube;
}

void DrawMoveableCube(MoveableCube *moveableCube) {
    float halfSize = moveableCube->size * moveableCube->base.scale / 2;

    // Draw cube
    DrawCube(moveableCube->base.position, moveableCube->size * moveableCube->base.scale, moveableCube->size * moveableCube->base.scale, moveableCube->size * moveableCube->base.scale, moveableCube->color);
    DrawCubeWires(moveableCube->base.position, moveableCube->size * moveableCube->base.scale, moveableCube->size * moveableCube->base.scale, moveableCube->size * moveableCube->base.scale, DARKGRAY);
}