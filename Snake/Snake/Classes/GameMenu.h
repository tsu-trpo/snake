#pragma  once

#include "cocos2d.h"
#include "Snake.h"
#include "AppDelegate.h"

using namespace cocos2d;

class GameMenu : public Layer
{
public:
    static Scene* createMenu();
    virtual bool init();

    void startGame(Ref* psender);
    void quit(Ref* psender);

    CREATE_FUNC(GameMenu);
};