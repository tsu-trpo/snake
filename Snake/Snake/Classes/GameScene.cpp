#include "GameScene.h"

Scene * GameScene::createGameScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if(!Scene::init())
    {
        return  false;
    }
    auto screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create(backgroundImage);
    background->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5));
    this->addChild(background,0);

    Score* score = new Score();
    addChild(score);

    auto Snake = Snake::create();
    addChild(Snake);

    return true;
}