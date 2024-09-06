#ifndef TANK_H
#define TANK_H

#include "gameobject.h"

#include "raylib.h"

#include "MoveableCube.h"

class Tank : public MoveableCube {
public:

    Tank(const Vector3& position, float rotation, float scale, float size, const Color& color);
    void Draw();
};

#endif // TANK_H