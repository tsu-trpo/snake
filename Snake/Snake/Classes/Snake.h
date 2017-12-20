#pragma once
#include "cocos2d.h"
#include "PartSnake.h"
#include <iostream>
#include "GlobalConstants.h"
#include "GameScene.h"
#include "Food.h"

class Snake : public Layer
{
    Size screenSize;
    Vec2 origin;

    int counterOfCollectedApples = 0;
public:

    float velocity = 0.05;

    PartSnake* head = nullptr;
    PartSnake* tail = nullptr;
    Vector<PartSnake*> snakeBodyPart;

    Food* apple = nullptr;

    EventKeyboard::KeyCode onKeyboardPressed(EventKeyboard::KeyCode keyCode, Event* event);

    void checkCollisionWithFood();
    void checkCollisionWithBody();

    void checkBorder();

    void addSnakePart();

    void update(float delta);

    virtual bool init();
    CREATE_FUNC(Snake);
};