#pragma once

#include "cocos2d.h"
#include "GlobalConstants.h"

using namespace cocos2d;

class Food : public Sprite
{
public:
    static Food* createApple();
    void spawnApple();
};
