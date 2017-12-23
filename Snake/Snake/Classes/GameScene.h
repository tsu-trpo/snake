#pragma once
#include "cocos2d.h"
#include "Snake.h"
#include "Score.h"

using namespace cocos2d;

class GameScene : public cocos2d::Scene
{
    Score* score;
public:

    static cocos2d::Scene* createGameScene();
    virtual bool init();

    CREATE_FUNC(GameScene);
};