#ifndef BASICRTSLOOP_H
#define BASICRTSLOOP_H

#include "GamePlayLoop.h"

class BasicRTSLoop : public GamePlayLoop {
public:
    BasicRTSLoop();
    void UpdateDrawFrame() override; // Override the virtual function

private:
    // Add any private member variables or methods here
};

#endif // BASICRTSLOOP_H