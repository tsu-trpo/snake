#include "menu.h"
#include "AppDelegate.h"
Scene* menu::createMenu()
{
    auto scene = Scene::create();
    auto layer = menu::create();
    scene->addChild(layer);
    return scene;
}

bool menu::init()
{
    if(!Node::init())
    {
        return  false;
    }

   MenuItemFont::setFontSize(30);

    Size screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("Snake", "fonts/arial.ttf", 60);
    label->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height - 100));
    label->setColor(Color3B(30.f, 100.f, 50.f));
    this->addChild(label);

    auto menuItemStart = MenuItemFont::create("Start Game", CC_CALLBACK_1(menu::startGame, this));

    auto menuItemQuit = MenuItemFont::create("Quit", CC_CALLBACK_1(menu::quit, this));

    auto menuCenter = Menu::create(menuItemStart,menuItemQuit, NULL);

    menuCenter->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5));

    menuCenter->setColor(Color3B(0.0f, 100.f, 0.0f));

    menuCenter->alignItemsVerticallyWithPadding(30);

    this->addChild(menuCenter);

    return true;
}

void menu::startGame(Ref* psender)
{
    auto scence = Snake::createSnake();
    Director::getInstance()->replaceScene(scence);
}

void menu::quit(Ref* psender)
{
    Director::getInstance()->end();
}