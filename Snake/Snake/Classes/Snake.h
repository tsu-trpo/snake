

#ifndef MYGAME_SNAKE_H
#define MYGAME_SNAKE_H

#include "cocos2d.h"
#include <cmath>
#include "partSnake.h"
#include "sizeGameScene.h"
#include "Food.h"
#include "Globals.h"
#include <vector>
#include "breakPoint.h"
using namespace cocos2d;

class Snake : public cocos2d::Layer
{
public:

    int lenght;
    int velocity;
    int score;

    bool gameOver;

    Size screenSize;

    Vec2 origin;

    Label *labelScore;

    breakPoint point;

    std::vector<breakPoint> breakPoints;
    partSnake* head;
    partSnake* tmpPartSnake;
    Vector<partSnake*> snakeBodyParts;
    partSnake* tail;


    Food* apple;

    static  cocos2d::Scene* createSnake();
    virtual bool init();

    void snakeHeadCollison(Sprite* sprt);

    EventKeyboard::KeyCode onKeyboardPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyboardReleased(EventKeyboard::KeyCode keyCode, Event* event);
    //void initializeKeyboardEvents();

    void update(float delta);

    CREATE_FUNC(Snake);
};



#endif //MYGAME_SNAKE_H
