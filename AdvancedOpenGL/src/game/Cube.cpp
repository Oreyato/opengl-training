#include "Cube.h"

#include "CubeMesh.h"
#include "../engine/Shader.h"

Cube::Cube(float xP, float yP, CubeMesh* cubeMeshP) :
    x { xP }, y { yP }, cubeMesh { cubeMeshP }
{
    setPosition(xP, yP);
}

Cube::~Cube(){
}

void Cube::load(){
}

void Cube::clean(){
}

void Cube::update(){

}

void Cube::draw(Shader& shader){
    shader.setMatrix4("mv_matrix", transform);
    cubeMesh->draw();
}

void Cube::setUniformScale(float scaleP) {
    
}

void Cube::setPosition(float xP, float yP) {
    x = xP;
    y = yP;

    transform = computeTransform();
}

Matrix4 Cube::computeTransform() {
    return Matrix4::createTranslation(Vector3(x, y, z));
}