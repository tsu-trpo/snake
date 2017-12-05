#include "Snake.h"

Scene * Snake::createSnake()
{
    auto scene = Scene::create();
    auto layer = Snake::create();
    scene->addChild(layer);
    return scene;
}

bool Snake::init()
{
    if(!Layer::init())
    {
        return  false;
    }
    auto screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    labelScore = Label::createWithTTF("Score: 0", "fonts/arial.ttf", 40);
    labelScore->setPosition(Vec2(origin.x + screenSize.width * 0.8, origin.y + screenSize.height * 0.95));
    this->addChild(labelScore,1);

    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5));
    this->addChild(background,0);
}