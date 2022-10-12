#include "Cube.h"

Cube::Cube(){
}

Cube::~Cube(){
}

void Cube::load(){

    static const GLfloat vertexPositions[] =
    {
        -0.25f, 0.25f, -0.25f,
        -0.25f, -0.25f, -0.25f,
        0.25f, -0.25f, -0.25f,

        0.25f, -0.25f, -0.25f,
        0.25f, 0.25f, -0.25f,
        -0.25f, 0.25f, -0.25f,
        
        0.25f, -0.25f, -0.25f,
        0.25f, -0.25f, 0.25f,
        0.25f, 0.25f, -0.25f,

        0.25f, -0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        0.25f, 0.25f, -0.25f,

        0.25f, -0.25f, 0.25f,
        -0.25f, -0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,

        -0.25f, -0.25f, 0.25f,
        -0.25f, 0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,

        -0.25f, -0.25f, 0.25f,
        -0.25f, -0.25f, -0.25f,
        -0.25f, 0.25f, 0.25f,
        
        -0.25f, -0.25f, -0.25f,
        -0.25f, 0.25f, -0.25f,
        -0.25f, 0.25f, 0.25f,

        -0.25f, -0.25f, 0.25f,
        0.25f, -0.25f, 0.25f,
        0.25f, -0.25f, -0.25f,

        0.25f, -0.25f, -0.25f,
        -0.25f, -0.25f, -0.25f,
        -0.25f, -0.25f, 0.25f,

        -0.25f, 0.25f, -0.25f,
        0.25f, 0.25f, -0.25f,
        0.25f, 0.25f, 0.25f,

        0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f, -0.25f
    };  

    // Generate data and put it in buffer object
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void Cube::clean(){

}

void Cube::update(){

}

void Cube::draw(){
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::setUniformScale(float scaleP) {
    
}