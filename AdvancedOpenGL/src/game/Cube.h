#ifndef Cube_H
#define Cube_H

#include "../engine/Assets.h"
#include "../engine/maths/Matrix4.h"

class CubeMesh;
class Shader;

class Cube
{
public:
    Cube(float xP, float yP, CubeMesh* cubeMeshP);
    ~Cube();
    void load();
    void clean();
    void update();
    void draw(Shader& shaderP);

    void setUniformScale(float scaleP);

    float getXPos() const { return x; };
    float getYPos() const { return y; };

    void setPosition(float xP, float yP);

    Matrix4 computeTransform();

private:
    GLuint buffer;

    float x { 0.0f };
    float y { 0.0f };
    float z { -4.0f };

    Matrix4 transform;

    CubeMesh* cubeMesh { nullptr };
};

#endif //Cube_H