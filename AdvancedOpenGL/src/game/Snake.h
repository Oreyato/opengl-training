#ifndef SNAKE_H
#define SNAKE_H

#include "BodyPart.h"
#include <vector>

class Snake
{
public:
    Snake(/* args */);
    ~Snake();

    void createSnake();

    void moveHead(float xP, float yP);
    void updateSnakePositions();

private:
    BodyPart snakeHead;
    std::vector<BodyPart> snakeBody;

};

#endif SNAKE_H