#ifndef MYGAME_PARTSNAKE_H
#define MYGAME_PARTSNAKE_H
#include "cocos2d.h"
#include <stdio.h>
#include <string.h>

using  namespace cocos2d;

class PartSnake : public Sprite
{
public:

    static PartSnake* createPartSnake(std::string nameSprite);
};

#endif