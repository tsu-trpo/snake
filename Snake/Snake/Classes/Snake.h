#pragma once
#include "cocos2d.h"
#include "PartSnake.h"
#include <iostream>
#include "GlobalConstants.h"

class Snake : public Layer
{
public:

    Size screenSize;
    Vec2 origin;

    float velocity = 0.05;

    PartSnake* head = nullptr;
    PartSnake* tail = nullptr;
    Vector<PartSnake*> snakeBodyPart;

    void snakeHeadCollisonWithBody();

    EventKeyboard::KeyCode onKeyboardPressed(EventKeyboard::KeyCode keyCode, Event* event);

    void update(float delta);

    virtual bool init();
    CREATE_FUNC(Snake);
};


