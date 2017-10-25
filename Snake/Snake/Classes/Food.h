//
// Created by user on 25.10.17.
//

#ifndef MYGAME_FOOD_H
#define MYGAME_FOOD_H

#include "cocos2d.h"

using namespace cocos2d;

class Food : public cocos2d::Sprite
{
public:
    static Food* create();
    void spawn();
};
#endif //MYGAME_FOOD_H
