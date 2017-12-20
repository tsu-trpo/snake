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

    apple = Food::createApple();
    apple->setRandomPositionApple();
    addChild(apple);

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
                head->moveDirection.setPoint(-1,0);
                head->setImage(snakeHeadLeftImage);
            }

            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            if(head->moveDirection.x != -1) {
                head->moveDirection.setPoint(1,0);
                head->setImage(snakeHeadRightImage);
            }
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            if(head->moveDirection.y != -1) {
                head->moveDirection.setPoint(0,1);
                head->setImage(snakeHeadUpImage);
            }

            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            if(head->moveDirection.y != 1) {
                head->moveDirection.setPoint(0,-1);
                head->setImage(snakeHeadDownImage);
            }
            break;
    }
}

void Snake::checkCollisionWithFood()
{
   if(head->getBoundingBox().intersectsRect(apple->getBoundingBox()))
   {
       PartSnake* newPartSnake = PartSnake::createPartSnake(snakePartHorizontallyImage);

       if(tail->moveDirection.y)
           newPartSnake->setImage(snakePartVerticallyImage);

       Vec2 newPartSnakePos = tail->getPosition();;

       newPartSnake->setPosition(newPartSnakePos);
       addChild(newPartSnake);
       snakeBodyPart.pushBack(newPartSnake);

       if(tail->moveDirection.x == 1) {
           tail->setPosition(newPartSnakePos.x - newPartSnake->getBoundingBox().size.width, newPartSnakePos.y);
       } else if(tail->moveDirection.x == -1) {
           tail->setPosition(newPartSnakePos.x + newPartSnake->getBoundingBox().size.width, newPartSnakePos.y);
       } else if(tail->moveDirection.y == 1) {
           tail->setPosition(newPartSnakePos.x, newPartSnakePos.y - newPartSnake->getBoundingBox().size.height);
       } else {
           tail->setPosition(newPartSnakePos.x, newPartSnakePos.y - newPartSnake->getBoundingBox().size.height);
       }

       counterOfCollectedApples++;

       apple->setRandomPositionApple();
   }

    if(counterOfCollectedApples == amountOfAppleTOAccelerate && velocity > minBorderVelocity)
    {
        velocity += acceleration;
        counterOfCollectedApples = 0;
        schedule(schedule_selector(Snake::update), velocity);
    }
}

void Snake::checkCollisionWithBody()
{
    for(auto &partSnake: snakeBodyPart)
    {
        if(head->getPosition() == partSnake->getPosition())
            unschedule(schedule_selector(Snake::update));
    }
    if(head->getPosition() == tail->getPosition())
        unschedule(schedule_selector(Snake::update));
}

void Snake::checkBorder()
{
    if(head->getPositionX() < origin.x )
        head->setPositionX(screenSize.width );
    if(head->getPositionX() > screenSize.width)
        head->setPositionX(origin.x );
    if(head->getPositionY() < origin.y)
        head->setPositionY(screenSize.height );
    if(head->getPositionY() > screenSize.height)
        head->setPositionY(origin.y);
}

void Snake::update(float delta)
{
    Vec2 previousPos = head->getPosition();
    Vec2 previousDir = head->moveDirection;

    Vec2 newHeadPos(head->getPositionX() + (head->moveDirection.x * snakeStepSize),
                    head->getPositionY() + (head->moveDirection.y * snakeStepSize));

    head->setPosition(newHeadPos);

    checkCollisionWithFood();
    checkCollisionWithBody();

    checkBorder();

    for(auto &partSnake: snakeBodyPart)
    {
        if (partSnake->moveDirection.x != 0)
        {
            partSnake->setImage(snakePartHorizontallyImage);
        } else
        {
            partSnake->setImage(snakePartVerticallyImage);
        }

        Vec2  partSnakePos = partSnake->getPosition();
        std::swap(partSnake->moveDirection, previousDir);
        partSnake->setPosition(previousPos);

        previousPos = partSnakePos;
    }

    std::swap(tail->moveDirection, previousDir);

    if(tail->moveDirection.x == 1) {
        tail->setImage(snakeTailRightImage);
    } else if(tail->moveDirection.x == -1) {
        tail->setImage(snakeTailLeftImage);
    } else if(tail->moveDirection.y == 1) {
        tail->setImage(snakeTailUpImage);
    } else {
        tail->setImage(snakeTailDownImage);
    }

    tail->setPosition(previousPos);
}