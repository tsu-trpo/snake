
#include "Snake.h"
#include <iostream>
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
    screenSize = Director::getInstance()->getVisibleSize();

    head = partSnake::create("SnakeHead.png");
    head->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5));
    this->addChild(head);
    int lenght = 3;

    Vector<partSnake*> partMass;

    for(int i = 0 ; i < 10; i++)
    {
        tmpPartSnake = partSnake::create("NewElemSnake.png");
        tmpPartSnake->setPosition(Vec2(VisibleRect::center().x - 45 + 13*i , VisibleRect::center().y ));
        partMass.pushBack(tmpPartSnake);
    }

    for (auto& partSnake: partMass)
    {
        addChild(partSnake);
    }

    tail = partSnake::create("SnakeTail.png");
    tail->setPosition(Vec2(VisibleRect::center().x -(40+20) , VisibleRect::center().y ));
    this->addChild(tail);

    /*for(int i = 0; i<lenght+2;i++)
    {
        std::cout << tailX[i] << " " << tailY[i] << std::endl;
    }*/

    snakeBodyParts = partMass;

    int scoreLabelSize = 0;
    scoreLabelSize = 40;
    labelScore = Label::createWithTTF("Score: 0", "fonts/arial.ttf", scoreLabelSize);
    labelScore->setPosition(Vec2(origin.x + screenSize.width * 0.8, origin.y + screenSize.height * 0.95));
    this->addChild(labelScore);

    apple = Food::create();
    //apple->setPosition(random(origin.x , origin.x + screenSize.width), random( origin.y ,origin.y + screenSize.height));
    apple->spawn();
    this->addChild(apple);

    gameOver = false;

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Snake::onKeyboardPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Snake::onKeyboardReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, head);

    return true;


}

EventKeyboard::KeyCode Snake::onKeyboardPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
             //head->xMovement--;
            if(head->xMovement!=0 || head->yMovement!=0) {
                point.setVar(head);
                breakPoints.push_back(point);
            }

                head->yMovement = 0;
                head->xMovement = -1;


            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
             //head->xMovement++;
            if(head->xMovement!=0 || head->yMovement!=0) {
                point.setVar(head);
                breakPoints.push_back(point);
            }

                head->yMovement = 0;
                head->xMovement = 1;

            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            //head->yMovement++;
            if(head->xMovement!=0 || head->yMovement!=0) {
                point.setVar(head);
                breakPoints.push_back(point);
            }

                head->yMovement = 1;
                head->xMovement = 0;

            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            //head->yMovement--;
            if(head->xMovement!=0 || head->yMovement!=0) {
                point.setVar(head);
                breakPoints.push_back(point);
            }

                head->yMovement = -1;
                head->xMovement = 0;


            break;
    }
    this->scheduleUpdate();

}

void Snake::onKeyboardReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
        switch (keyCode)
        {
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_A:
                //breakPoints.push_back(head);
                //head->xMovement++;
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
                //breakPoints.push_back(head);
                //head->xMovement--;
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            case EventKeyboard::KeyCode::KEY_W:
                //breakPoints.push_back(head);
                //head->yMovement--;
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
                //breakPoints.push_back(head);
                //head->yMovement++;
                break;
        }


}

void Snake::update(float delta)
{
    float headPosX = head->getPositionX() ;
    float headPosY = head->getPositionY();
    float tmpX;
    float tmpY;

    float newPosX = head->getPositionX() + (head->xMovement * 5.f);
    float newPosY = head->getPositionY() + (head->yMovement * 5.f);
    head->setPosition(newPosX, newPosY);

    for(auto &partSnake: snakeBodyParts)
    {
        tmpX = partSnake->getPositionX() ;
        tmpY = partSnake->getPositionY();
        partSnake->setPosition(headPosX,headPosY);
        headPosX = tmpX;
        headPosY = tmpY;
    }

}




