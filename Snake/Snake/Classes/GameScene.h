#pragma once
#include "cocos2d.h"
#include "Snake.h"

using namespace cocos2d;

class GameScene : public cocos2d::Scene
{
    Label *labelScore;
public:

    static cocos2d::Scene* createGameScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
};

