
#ifndef MYGAME_PARTSNAKE_H
#define MYGAME_PARTSNAKE_H

#include "cocos2d.h"
#include <stdio.h>
#include <string.h>
class partSnake : public cocos2d::Sprite
{
public:
    static partSnake* create(std::string name);
    int xMovement = 0;
    int yMovement = 0;
};
#endif //MYGAME_PARTSNAKE_H
