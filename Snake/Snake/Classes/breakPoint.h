
#ifndef MYGAME_BREAKPOINT_H
#define MYGAME_BREAKPOINT_H
#include "partSnake.h"
//#include "cocos2d.h"

using namespace cocos2d;

class breakPoint
{
public:
    int xMovement;
    int yMovement;
    //Vec2 breakPointVec2;
    int posX;
    int posY;
    void setVar(partSnake* part);
};
#endif //MYGAME_BREAKPOINT_H
