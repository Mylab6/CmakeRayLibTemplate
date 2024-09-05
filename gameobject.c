#include "gameobject.h"

void TranslateGameObject(GameObject *obj, Vector3 translation) {
    obj->position.x += translation.x;
    obj->position.y += translation.y;
    obj->position.z += translation.z;
}

void RotateGameObject(GameObject *obj, float angle) {
    obj->rotation += angle;
}

GameObject CreateGameObject(Vector3 position, float rotation, float scale) {
    GameObject obj = {
        .position = position,
        .rotation = rotation,
        .scale = scale,
        .Translate = TranslateGameObject,
        .Rotate = RotateGameObject
    };
    return obj;
}