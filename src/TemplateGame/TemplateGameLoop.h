#ifndef TemplateGameLoop_H
#define TemplateGameLoop_H

#include "../engine/GamePlayLoop.h"

class TemplateGameLoop : public GamePlayLoop {
public:
    TemplateGameLoop();
    void UpdateDrawFrame() override; // Override the virtual function

private:
    // Add any private member variables or methods here
};

#endif // BASICRTSLOOP_H