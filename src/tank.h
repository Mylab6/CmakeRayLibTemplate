#ifndef TANK_H
#define TANK_H

#include "gameobject.h"

#include "raylib.h"

#include "MoveableCube.h"

class Tank : public MoveableCube {
public:

    Tank(Vector3 position, float rotation, float scale, Color color,Vector3 velocity);
    void Draw() override;
};

#endif // TANK_HA