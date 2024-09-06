#ifndef TANK_H
#define TANK_H


#include "raylib.h"

#include "../engine/MoveableCube.h"

class Tank : public MoveableCube {
public:

    Tank(const Vector3& position, float rotation, float scale, Color color, const Vector3& velocity = {0.0f, 0.0f, 0.0f});
    void Draw();
};

#endif // TANK_H