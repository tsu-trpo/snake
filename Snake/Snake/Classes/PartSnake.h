#pragma once
#include "cocos2d.h"
#include <string>

using  namespace cocos2d;

class PartSnake : public Sprite
{
public:
    int xMovement = 1;
    int yMovement = 0;

    static PartSnake* createPartSnake(const std::string &nameSprite);
};

