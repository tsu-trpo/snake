
#ifndef MYGAME_PARTSNAKE_H
#define MYGAME_PARTSNAKE_H

#include "cocos2d.h"
#include <stdio.h>
#include <string.h>
class partSnake : public cocos2d::Sprite
{
public:
    static partSnake* create(std::string name);
    void rotate(std::string name);
    int xMovement = 1;
    int yMovement = 0;
    int lastXMov ;
    int lastYMov ;
};
#endif //MYGAME_PARTSNAKE_H
