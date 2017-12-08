#include "Snake.h"

Layer* Snake::createSnake()
{
    auto layer = Snake::create();

    return layer;
}

bool Snake::init()
{
    if(!Layer::init())
    {
        return  false;
    }

    auto screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    head = PartSnake::createPartSnake("SnakeHead.png");
    head->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5));
    this->addChild(head);

    int lenght = 3;

    PartSnake* tmpPartSnake;

    for(int i = 0; i < lenght; i++)
    {
        tmpPartSnake = PartSnake::createPartSnake("NewElemSnake.png");
        tmpPartSnake->setPosition(Vec2(origin.x + screenSize.width * 0.5 - 45 + 13*i , origin.y + screenSize.height * 0.5));
        snakeBodyPart.pushBack(tmpPartSnake);
    }

    for (auto& partSnake: snakeBodyPart)
    {
        addChild(partSnake);
    }

    tail = PartSnake::createPartSnake("SnakeTail.png");
    tail->setPosition(Vec2(origin.x + screenSize.width * 0.5 -(40+20) , origin.y + screenSize.height * 0.5));
    this->addChild(tail);

    return true;
}