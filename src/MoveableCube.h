#ifndef MOVEABLECUBE_H
#define MOVEABLECUBE_H

#include "gameobject.h"
#include "raylib.h"

class MoveableCube : public GameObject {
public:
  
    
    Color color;

    MoveableCube(Vector3 position, float rotation, float scale,  Color color,Vector3 velocity );
    void Draw() override;
};

#endif // MOVEABLECUBE_H