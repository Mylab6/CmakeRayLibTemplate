#include "gameobject.h"

void TranslateGameObject(GameObject *obj, Vector2 translation) {
    obj->position.x += translation.x;
    obj->position.y += translation.y;
}

void RotateGameObject(GameObject *obj, float angle) {
    obj->rotation += angle;
}

GameObject CreateGameObject(Vector2 position, float rotation, float scale) {
    GameObject obj = {
        .position = position,
        .rotation = rotation,
        .scale = scale,
        .Translate = TranslateGameObject,
        .Rotate = RotateGameObject
    };
    return obj;
}