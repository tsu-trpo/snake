#pragma once
#include "cocos2d.h"
#include <string>
#include "Direction.h"

using  namespace cocos2d;

class PartSnake : public Sprite
{
public:
    Direction moveDirection = Direction::right;

    Vec2 getDirectionVec2();

    void setImage(const std::string &name);

    static PartSnake* createPartSnake(const std::string &nameSprite);
};

