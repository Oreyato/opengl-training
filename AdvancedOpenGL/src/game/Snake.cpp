#include "Snake.h"

Snake::Snake(/* args */)
{
}

Snake::~Snake()
{
}

void Snake::createSnake() {
    // Create the head

    // Add it inside the body vector

    // Create every other parts

        // Emplace back them inside the vector
}

void Snake::moveHead(float xP, float yP) {

}

void Snake::updateBodyPos() {
    for (int i = snakeBody.size(); i < 0; i--)
    {
        // Get next body part position
        float newXpos = snakeBody[i - 1].getXPos();
        float newYpos = snakeBody[i - 1].getYPos();
        float newZPos = snakeBody[i - 1].getZPos();

        snakeBody[i].setPosition(newXpos, newYpos, newZPos);
    }
    
}