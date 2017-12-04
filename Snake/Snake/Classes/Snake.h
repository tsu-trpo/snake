#ifndef MYGAME_SNAKE_H
#define MYGAME_SNAKE_H

#include "cocos2d.h"

using namespace cocos2d;

class Snake : public cocos2d::Layer
{

public:
    Label *labelScore;

    static cocos2d::Scene* createSnake();

    virtual bool init();

    CREATE_FUNC(Snake);
};

#endif
