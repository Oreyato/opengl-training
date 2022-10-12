#ifndef Cube_H
#define Cube_H

#include "../engine/Assets.h"

class Cube
{
public:
    Cube(/* args */);
    ~Cube();
    void load();
    void clean();
    void update();
    void draw();

    void setUniformScale(float scaleP);

private:
    GLuint buffer;
};

#endif //Cube_H