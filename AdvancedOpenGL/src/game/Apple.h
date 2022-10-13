#ifndef APPLE_H
#define APPLE_H

#include "Cube.h"

class Apple: 
    public Cube
{
public:
    Apple(float xP, float yP, float zP, CubeMesh* cubeMeshP, float uniScaleP = 1.0f);
    ~Apple();

    void update();

    //v Auto rotation =======================================
    float getZRotSpeed() { return zRotSpeed; };
    void setZRotSpeed(float zRotSpeedP);

    //^ Auto rotation =======================================
    //v Interactions ========================================
    void pickUp();

    //^ Interactions ========================================

private:
    float zRotSpeed { 0.0f };

};

#endif // APPLE_H