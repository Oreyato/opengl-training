#include "Snake.h"
#include "../engine/Timer.h"


#include <cstdlib>
#include <ctime>

Snake::Snake(float xP, float yP, float zP, float scaleP, float stepSizeP, float delayP, int segmentNbP, CubeMesh* headMeshP, CubeMesh* bodyPartMeshP) :
    x { xP }, y { yP }, z { zP }, scale { scaleP }, stepSize { stepSizeP }, delay { delayP }, segmentNb { segmentNbP }, headMesh { headMeshP }, bodyPartMeshP { bodyPartMeshP }
{
    createSnake();    
}

Snake::~Snake()
{
}

void Snake::createSnake() {
    // Create the head
    snakeHead = BodyPart(x, y, z, headMesh, scale);
    // Add it inside the body vector
    snakeBody.emplace_back(snakeHead);

    // Create every other parts
    float offset = stepSize * scale * 0.85;

    for (int i = 1; i < segmentNb + 1; i++)
    {
        BodyPart bodypart = BodyPart(x - offset*i, y, z, bodyPartMeshP, scale*0.85);
        // Emplace back them inside the vector
        snakeBody.emplace_back(bodypart);
    }
}

void Snake::load() {

}

void Snake::clean() {

}

void Snake::update() {
    timer += 1.0f;

    if (timer >= delay * 100.0f) {
        updateBodyPos();

        timer -= delay * 100.0f;
    }    
}

void Snake::draw(Shader& shaderP) {
    for (auto& snakePart : snakeBody)
    {
        snakePart.draw(shaderP);
    }
    
}

void Snake::moveHead() {
    x = x + stepSize*moveDirection.x;
    y = y + stepSize*moveDirection.y;
    z = z + stepSize*moveDirection.z;

    // Change head position toward a direction every "delay"
    snakeBody[0].setPosition(x, y, z);

    // The direction can be changed by keyboard inputs
}

void Snake::updateBodyPos() {
    for (int i = snakeBody.size() - 1; i > 0; --i)
    {
        // Get next body part position
        float newXpos = snakeBody[i - 1].getXPos();
        float newYpos = snakeBody[i - 1].getYPos();
        float newZPos = snakeBody[i - 1].getZPos();

        snakeBody[i].setPosition(newXpos, newYpos, newZPos);
    }
    
    moveHead(); // placeholder values
}