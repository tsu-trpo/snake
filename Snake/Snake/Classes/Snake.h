#pragma once
#include "cocos2d.h"
#include "PartSnake.h"
#include <iostream>
class Snake : public Layer
{
public:

    PartSnake* head = nullptr;
    PartSnake* tail = nullptr;
    Vector<PartSnake*> snakeBodyPart;

    virtual bool init();
    CREATE_FUNC(Snake);
};


