#ifndef SNAKE_H
#define SNAKE_H

#include "BodyPart.h"
#include <vector>

class Snake
{
public:
    Snake(/* args */);
    ~Snake();

private:
    std::vector<BodyPart> snakeBody;

};

#endif SNAKE_H