#include "Snake.h"

bool Snake::init()
{
    if(!Layer::init())
    {
        return  false;
    }

    auto screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    head = PartSnake::createPartSnake(snakeHeadImage);
    head->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5));
    this->addChild(head);

    int length = 3;

    for(int i = 0; i < length; i++)
    {
        PartSnake*  partSnake = PartSnake::createPartSnake(snakePartImage);
        partSnake->setPosition(Vec2(head->getPositionX() - (head->getBoundingBox().size.width/2 + partSnake->getBoundingBox().size.width * i) , head->getPositionY()));
        snakeBodyPart.pushBack(partSnake);
    }

    for (auto& partSnake: snakeBodyPart)
    {
        addChild(partSnake);
    }

    tail = PartSnake::createPartSnake(snakeTailImage);
    tail->setPosition(Vec2(head->getPositionX() - (head->getBoundingBox().size.width/2  + snakeBodyPart.back()->getBoundingBox().size.width * length) , head->getPositionY()));
    this->addChild(tail);

    velocity = 0.05;

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Snake::onKeyboardPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, head);

    return true;
}

EventKeyboard::KeyCode Snake::onKeyboardPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            if(head->xMovement != 1) {
                head->yMovement = 0;
                head->xMovement = -1;
            }

            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            if(head->xMovement != -1) {
                head->yMovement = 0;
                head->xMovement = 1;
            }
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            if(head->yMovement != -1) {
                head->yMovement = 1;
                head->xMovement = 0;
            }

            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            if(head->yMovement != 1) {
                head->yMovement = -1;
                head->xMovement = 0;
            }
            break;
    }
    this->schedule(schedule_selector(Snake::update), velocity);

}

void Snake::update(float delta)
{
    float headPosX = head->getPositionX();
    float headPosY = head->getPositionY();

    float newPosX = head->getPositionX() + (head->xMovement * oneStep);
    float newPosY = head->getPositionY() + (head->yMovement * oneStep);
    head->setPosition(newPosX, newPosY);
    
    for(auto &partSnake: snakeBodyPart)
    {
        float partSnakePosX = partSnake->getPositionX();
        float partSnakePosY = partSnake->getPositionY();

        partSnake->setPosition(headPosX,headPosY);

        headPosX = partSnakePosX;
        headPosY = partSnakePosY;
    }

    tail->setPosition(headPosX,headPosY);

}