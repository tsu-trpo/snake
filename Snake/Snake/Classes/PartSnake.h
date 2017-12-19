#pragma once
#include "cocos2d.h"
#include <string>

using  namespace cocos2d;

class PartSnake : public Sprite
{
public:
    Vec2 moveDirection{1,0};

    void setImage(const std::string &name);

    static PartSnake* createPartSnake(const std::string &nameSprite);
};

