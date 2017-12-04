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
    if(!Node::init())
    {
        return  false;
    }
    auto screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    labelScore = Label::createWithTTF("Score: 0", "fonts/arial.ttf", 40);
    labelScore->setPosition(Vec2(origin.x + screenSize.width * 0.8, origin.y + screenSize.height * 0.95));
    this->addChild(labelScore);
}