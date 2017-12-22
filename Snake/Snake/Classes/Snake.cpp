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
            if(head->moveDirection != Direction::right) {
                head->moveDirection = Direction ::left;
                head->setImage(snakeHeadLeftImage);
            }

            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            if(head->moveDirection != Direction ::left) {
                head->moveDirection = Direction::right;
                head->setImage(snakeHeadRightImage);
            }
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            if(head->moveDirection != Direction ::down) {
                head->moveDirection = Direction::up;
                head->setImage(snakeHeadUpImage);
            }

            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            if(head->moveDirection != Direction::up) {
                head->moveDirection = Direction::down;
                head->setImage(snakeHeadDownImage);
            }
            break;
    }
}

void Snake::addSnakePart()
{
    PartSnake* newPartSnake = PartSnake::createPartSnake(snakePartHorizontallyImage);

    if(tail->moveDirection == Direction::up || tail->moveDirection == Direction::down) {
        newPartSnake->setImage(snakePartVerticallyImage);
    }

    Vec2 newPartSnakePos = tail->getPosition();

    newPartSnake->setPosition(newPartSnakePos);
    addChild(newPartSnake);
    snakeBodyPart.pushBack(newPartSnake);

    Vec2 tailMoveDirection = tail->getDirectionVec2();
    Vec2 distanceBetweenSprites(tailMoveDirection.x * newPartSnake->getBoundingBox().size.height,
                                tailMoveDirection.y * newPartSnake->getBoundingBox().size.width);
    tail->setPosition(tail->getPosition() - distanceBetweenSprites);
}

void Snake::checkCollisionWithFood()
{
   if(head->getBoundingBox().intersectsRect(apple->getBoundingBox()))
   {
       counterOfCollectedApples++;

       addSnakePart();

       apple->setRandomPositionApple();
   }

    if(counterOfCollectedApples == amountOfAppleToAccelerate && velocity > minBorderVelocity)
    {
        velocity += speedIncrease;
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
    Direction previousDir = head->moveDirection;

    Vec2 stepDerection = head->getDirectionVec2();

    Vec2 newHeadPos(head->getPositionX() + (stepDerection.x * snakeStepSize),
                    head->getPositionY() + (stepDerection.y * snakeStepSize));

    head->setPosition(newHeadPos);

    checkCollisionWithFood();
    checkCollisionWithBody();

    checkBorder();

    for(auto &partSnake: snakeBodyPart)
    {
        std::swap(partSnake->moveDirection, previousDir);

        switch(partSnake->moveDirection) {
            case Direction::up:
            case Direction::down:
                partSnake->setImage(snakePartVerticallyImage); break;
            case Direction::left:
            case Direction::right:
                partSnake->setImage(snakePartHorizontallyImage); break;
            default:
                throw std::logic_error{"Unexpected case"};
        }

        Vec2  partSnakePos = partSnake->getPosition();
        partSnake->setPosition(previousPos);
        previousPos = partSnakePos;
    }

    std::swap(tail->moveDirection, previousDir);

    switch(tail->moveDirection) {
        case Direction::up:
            tail->setImage(snakeTailUpImage); break;
        case Direction::down:
            tail->setImage(snakeTailDownImage); break;
        case Direction::left:
            tail->setImage(snakeTailLeftImage); break;
        case Direction::right:
            tail->setImage(snakeTailRightImage); break;
        default:
            throw std::logic_error{"Unexpected case"};
    }

    tail->setPosition(previousPos);
}