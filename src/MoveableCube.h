#ifndef MOVEABLECUBE_H
#define MOVEABLECUBE_H

#include "gameobject.h"
#include "raylib.h"

class MoveableCube : public GameObject {
public:
  
    float size;
    Color color;

    MoveableCube(const Vector3& position, float rotation, float scale, float size, const Color& color);
    void Draw();
};

#endif // MOVEABLECUBE_H