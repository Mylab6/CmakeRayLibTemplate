#ifndef MOVEABLECUBE_H
#define MOVEABLECUBE_H

#include "gameobject.h"
#include "raylib.h"

class MoveableCube : public GameObject {
public:
  
    
    Color color;

    MoveableCube(const Vector3& position, float rotation, float scale,  Color color,const Vector3& velocity = {0.0f, 0.0f, 0.0f});
    void Draw();
};

#endif // MOVEABLECUBE_H