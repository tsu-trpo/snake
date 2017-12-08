#pragma once
#include "cocos2d.h"
#include <string>

using  namespace cocos2d;

class PartSnake : public Sprite
{
public:

    static PartSnake* createPartSnake(std::string nameSprite);
};

