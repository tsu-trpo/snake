#include "Snake.h"

bool Snake::init()
{
    if(!Layer::init())
    {
        return  false;
    }

     screenSize = Director::getInstance()->getVisibleSize();
     origin = Director::getInstance()->getVisibleOrigin();

    head = PartSnake::createPartSnake(snakeHeadRightImage);
    head->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5));
    addChild(head);

    int length = 3;

    for(int i = 0; i < length; i++)
    {
        PartSnake*  partSnake = PartSnake::createPartSnake(snakePartHorizontallyImage);
        partSnake->setPosition(Vec2(head->getPositionX() - (head->getBoundingBox().size.width/2 + partSnake->getBoundingBox().size.width * i) ,
                                    head->getPositionY()));
        snakeBodyPart.pushBack(partSnake);
    }

    for (auto& partSnake: snakeBodyPart)
    {
        addChild(partSnake);
    }

    tail = PartSnake::createPartSnake(snakeTailRightImage);
    tail->setPosition(Vec2(head->getPositionX() - (head->getBoundingBox().size.width/2  + snakeBodyPart.back()->getBoundingBox().size.width * length) ,
                           head->getPositionY()));
    addChild(tail);

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Snake::onKeyboardPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, head);

    schedule(schedule_selector(Snake::update), velocity);

    return true;
}

EventKeyboard::KeyCode Snake::onKeyboardPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            if(head->moveDirection.x != 1) {
                head->previousDirection = head->moveDirection;
                head->moveDirection.setPoint(-1,0);
                head->setImage(snakeHeadLeftImage);
            }

            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            if(head->moveDirection.x != -1) {
                head->previousDirection = head->moveDirection;
                head->moveDirection.setPoint(1,0);
                head->setImage(snakeHeadRightImage);
            }
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            if(head->moveDirection.y != -1) {
                head->previousDirection = head->moveDirection;
                head->moveDirection.setPoint(0,1);
                head->setImage(snakeHeadUpImage);
            }

            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            if(head->moveDirection.y != 1) {
                head->previousDirection = head->moveDirection;
                head->moveDirection.setPoint(0,-1);
                head->setImage(snakeHeadDownImage);
            }
            break;
    }
}

void Snake::update(float delta)
{
    Vec2 headPos = head->getPosition();
    Vec2 previousDir = head->moveDirection;

    Vec2 newHeadPos(head->getPositionX() + (head->moveDirection.x * snakeStepSize),
                    head->getPositionY() + (head->moveDirection.y * snakeStepSize));

    head->setPosition(newHeadPos);

    for(auto &partSnake: snakeBodyPart)
    {
        Vec2  partSnakePos = partSnake->getPosition();
        partSnake->previousDirection = partSnake->moveDirection;
        partSnake->moveDirection = previousDir;

        if(partSnake->moveDirection.x == 1 || partSnake->moveDirection.x == -1)
        {
            partSnake->setImage(snakePartHorizontallyImage);
        }
        if(partSnake->moveDirection.y == 1 || partSnake->moveDirection.y == -1)
        {

            partSnake->setImage(snakePartVerticallyImage);
        }

        partSnake->setPosition(headPos);

        headPos = partSnakePos;
        previousDir = partSnake->previousDirection;
    }

    if(previousDir.x == 1)
    {
        tail->setImage(snakeTailRightImage);
    }
    if(previousDir.x == -1)
    {
        tail->setImage(snakeTailLeftImage);
    }
    if(previousDir.y == 1)
    {
        tail->setImage(snakeTailUpImage);
    }
    if(previousDir.y == -1)
    {
        tail->setImage(snakeTailDownImage);
    }

    tail->setPosition(headPos);
}