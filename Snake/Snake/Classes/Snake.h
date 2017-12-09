#pragma once
#include "cocos2d.h"
#include "PartSnake.h"
#include <iostream>
#include "GlobalConstants.h"
#include "Food.h"

class Snake : public Layer
{
public:

    PartSnake* head = nullptr;
    PartSnake* tail = nullptr;
    Vector<PartSnake*> snakeBodyPart;

    virtual bool init();
    CREATE_FUNC(Snake);
};


