#ifndef MYGAME_SNAKE_H
#define MYGAME_SNAKE_H

#include "cocos2d.h"
#include "PartSnake.h"
#include "GameScene.h"

class Snake : public Layer
{
public:

    PartSnake* head;
    PartSnake* tail;
    Vector<PartSnake*> snakeBodyPart;

    static Layer* createSnake();
    virtual bool init();
    CREATE_FUNC(Snake);
};

#endif
