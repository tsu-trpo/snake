#include "Snake.h"

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

    int length = 3;

    for(int i = 0; i < length; i++)
    {
        PartSnake* tmp;
        tmp = PartSnake::createPartSnake("NewElemSnake.png");
        tmp->setPosition(Vec2(head->getPositionX() - (head->getBoundingBox().size.width/2 + tmp->getBoundingBox().size.width * i) , head->getPositionY()));
        snakeBodyPart.pushBack(tmp);
    }

    for (auto& partSnake: snakeBodyPart)
    {
        addChild(partSnake);
    }

    tail = PartSnake::createPartSnake("SnakeTail.png");
    tail->setPosition(Vec2(head->getPositionX() - (head->getBoundingBox().size.width/2  + snakeBodyPart.back()->getBoundingBox().size.width * length) , head->getPositionY()));
    this->addChild(tail);

    return true;
}