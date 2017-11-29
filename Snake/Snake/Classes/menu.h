//
// Created by user on 29.11.17.
//

#ifndef MYGAME_MENU_H
#define MYGAME_MENU_H

#include "cocos2d.h"
#include "Snake.h"

class menu : public cocos2d::Layer
{
public:
    static  cocos2d::Scene* createMenu();
    virtual bool init();

    void startGame(Ref* psender);
    void quit(Ref* psender);

    CREATE_FUNC(menu);
};
#endif //MYGAME_MENU_H
