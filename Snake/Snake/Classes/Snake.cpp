
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

    head = partSnake::create("SnakeHeadRight.png");
    head->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5));
    this->addChild(head);
    int lenght = 3;

    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(Snake::menu, this));

    closeItem->setPosition(Vec2(origin.x + screenSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    Vector<partSnake*> partMass;

    for(int i = 0 ; i < lenght; i++)
    {
        tmpPartSnake = partSnake::create("NewElemSnakeLR.png");
        tmpPartSnake->setPosition(Vec2(VisibleRect::center().x - 45 + 13*i , VisibleRect::center().y ));
        partMass.pushBack(tmpPartSnake);
    }

    for (auto& partSnake: partMass)
    {
        addChild(partSnake);
    }

    tail = partSnake::create("SnakeTailRight.png");
    tail->setPosition(Vec2(VisibleRect::center().x -(40+20) , VisibleRect::center().y ));
    this->addChild(tail);

    snakeBodyParts = partMass;

    int scoreLabelSize = 0;
    scoreLabelSize = 40;
    labelScore = Label::createWithTTF("Score: 0", "fonts/arial.ttf", scoreLabelSize);
    labelScore->setPosition(Vec2(origin.x + screenSize.width * 0.8, origin.y + screenSize.height * 0.95));
    this->addChild(labelScore);

    startText = Label::createWithTTF("Click D to start", "fonts/arial.ttf", scoreLabelSize);
    startText->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5 + 100));
    this->addChild(startText);

    apple = Food::create();
    apple->spawn();
    this->addChild(apple);

    score = 0;
    velocity = 0.03;


    bool gameStart = false;

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Snake::onKeyboardPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Snake::onKeyboardReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, head);



    return true;


}

void Snake::menu(Ref* psender)
{
    auto scence = menu::createMenu();
    Director::getInstance()->replaceScene(scence);
}

void Snake::menuESC()
{
    auto scence = menu::createMenu();
    Director::getInstance()->replaceScene(scence);
}

EventKeyboard::KeyCode Snake::onKeyboardPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            if(head->xMovement != 1) {
                head->lastXMov = head->xMovement;
                head->lastYMov = head->yMovement;
                head->yMovement = 0;
                head->xMovement = -1;
            }

            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            if(head->xMovement != -1) {
                if (!gameStart) {
                    removeChild(startText);
                    gameStart = true;
                }

                head->lastXMov = head->xMovement;
                head->lastYMov = head->yMovement;
                head->yMovement = 0;
                head->xMovement = 1;
            }
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            if(head->yMovement != -1) {
                head->lastXMov = head->xMovement;
                head->lastYMov = head->yMovement;
                head->yMovement = 1;
                head->xMovement = 0;
            }

            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            if(head->yMovement != 1) {
                head->lastXMov = head->xMovement;
                head->lastYMov = head->yMovement;
                head->yMovement = -1;
                head->xMovement = 0;
            }
            break;
        case EventKeyboard::KeyCode ::KEY_ESCAPE:
            menuESC();
            break;
    }
    this->schedule(schedule_selector(Snake::update), velocity);

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

bool Snake::snakeHeadCollisonWithBody()
{

    for(auto &partSnake: snakeBodyParts)
    {
        if(head->getBoundingBox().intersectsRect(partSnake->getBoundingBox()))
        {
            return true;
        }
    }
    if(head->getBoundingBox().intersectsRect(tail->getBoundingBox()))
    {
        return true;
    }
    return false;
}

void Snake::snakeHeadCollisonWithFood()
{
    if(head->getBoundingBox().intersectsRect(apple->getBoundingBox()))
    {
        apple->spawn();
        score++;
        std::stringstream ss;
        ss << score;
        std::string ScoreString = ss.str();
        std::string gameScoreString = "Score:" + ScoreString;
        labelScore->setString(gameScoreString.c_str());

        tmpPartSnake = partSnake::create("NewElemSnakeLR.png");
        float posX = tail->getPositionX();
        float posY = tail->getPositionY();
        float posNewElemX = tail->getPositionX();
        float posNewElemY = tail->getPositionY();
        if(tail->lastXMov == 1) posX -= 13;
        if(tail->lastYMov == 1) posY -= 13;
        if(tail->lastXMov == -1) posX += 13;
        if(tail->lastYMov == -1) posY += 13;
        tail->setPosition(posX,posY);
        tmpPartSnake->setPosition(posNewElemX,posNewElemY);
        addChild(tmpPartSnake);
        snakeBodyParts.pushBack(tmpPartSnake);

        countApple++;
    }

    if(countApple == 5)
    {
        velocity -= 0.001;
        countApple = 0;
    }
}

void Snake::endGame()
{
    endText = Label::createWithTTF("Уou lose, press ESC", "fonts/arial.ttf", 40);
    endText->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5 + 100));
    this->addChild(endText);

    this->unschedule(schedule_selector(Snake::update));
}

void Snake::update(float delta)
{
    float headPosX = head->getPositionX();
    float headPosY = head->getPositionY();
    float tmpX;
    float tmpY;

    int lastDirX = head->lastXMov;
    int lastDirY = head->lastYMov;

    float newPosX = head->getPositionX() + (head->xMovement * 14);
    float newPosY = head->getPositionY() + (head->yMovement * 14);
    head->setPosition(newPosX, newPosY);

    if(head->getPositionX() < VisibleRect::left().x) head->setPositionX(VisibleRect::right().x-30);
    if(head->getPositionX() > VisibleRect::right().x) head->setPositionX( VisibleRect::left().x +30);
    if(head->getPositionY() <  VisibleRect::bottom().y) head->setPositionY(VisibleRect::top().y-30);
    if(head->getPositionY() > VisibleRect::top().y) head->setPositionY(VisibleRect::bottom().y + 30);

    if(snakeHeadCollisonWithBody())
    {
        endGame();
    }
    snakeHeadCollisonWithFood();


    if(head->xMovement == -1) {
        head->rotate("SnakeHeadLeft.png");
    }
    if(head->xMovement == 1) {
        head->rotate("SnakeHeadRight.png");}
    if(head->yMovement == -1) {
        head->rotate("SnakeHeadDown.png");
    }
    if(head->yMovement == 1) {
        head->rotate("SnakeHeadUp.png");
    }

    if(head->yMovement == 0 && head->xMovement == 1)headPosX = headPosX - (30 - 14) ;
    if(head->yMovement == 0 && head->xMovement == -1)headPosX = headPosX + (30 - 14) ;
    if(head->yMovement == 1 && head->xMovement ==0) headPosY = headPosY - (28 - 14);
    if(head->yMovement == -1 && head->xMovement == 0)headPosY = headPosY + (28 - 14) ;

    for(auto &partSnake: snakeBodyParts)
    {
        tmpX = partSnake->getPositionX();
        tmpY = partSnake->getPositionY();
        partSnake->lastXMov = partSnake->xMovement;
        partSnake->lastYMov = partSnake->yMovement;

        partSnake->xMovement = lastDirX;
        partSnake->yMovement = lastDirY;

        if(partSnake->yMovement == 0 && partSnake->xMovement == 1) {

            partSnake->rotate("NewElemSnakeLR.png");
        }
        if(partSnake->yMovement == 0 && partSnake->xMovement == -1)
        {

            partSnake->rotate("NewElemSnakeLR.png");
        }
        if(partSnake->xMovement == 0 && partSnake->yMovement == 1)
        {

            partSnake->rotate("NewElemSnakeUD.png");
        }
        if(partSnake->xMovement == 0 && partSnake->yMovement == -1)
        {

            partSnake->rotate("NewElemSnakeUD.png");
        }

        partSnake->setPosition(headPosX,headPosY);
        headPosX = tmpX;
        headPosY = tmpY;
        lastDirX = partSnake->lastXMov;
        lastDirY = partSnake->lastYMov;

    }


    tail->setPosition(headPosX,headPosY);
    tail->lastXMov = lastDirX;
    tail->lastYMov = lastDirY;
    if(tail->lastXMov == -1) {
        tail->rotate("SnakeTailLeft.png");
    }
    if(tail->lastXMov == 1) {
        tail->rotate("SnakeTailRight.png");}
    if(tail->lastYMov == -1) {
        tail->rotate("SnakeTailDown.png");
    }
    if(tail->lastYMov == 1) {
        tail->rotate("SnakeTailUp.png");
    }

    head->lastXMov = head->xMovement;
    head->lastYMov = head->yMovement;
}




