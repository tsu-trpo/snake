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

    labelScore = Label::createWithTTF("Score: 0", "fonts/arial.ttf", 40);
    labelScore->setPosition(Vec2(origin.x + screenSize.width * 0.8, origin.y + screenSize.height * 0.95));
    this->addChild(labelScore,1);

    auto background = Sprite::create(backgroundImage);
    background->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5));
    this->addChild(background,0);

    auto Snake = Snake::create();
    this->addChild(Snake);

    auto apple = Food::createApple();
    apple->setRandomPositionApple();
    this->addChild(apple);

    return true;
}