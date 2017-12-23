#include "GameMenu.h"

Scene* GameMenu::createMenu()
{
    auto scene = Scene::create();
    auto layer = GameMenu::create();
    scene->addChild(layer);
    return scene;
}

bool GameMenu::init()
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
    addChild(label);

    auto menuItemStart = MenuItemFont::create("Start Game", CC_CALLBACK_1(GameMenu::startGame, this));
    auto menuItemQuit = MenuItemFont::create("Quit", CC_CALLBACK_1(GameMenu::quit, this));
    auto menuCenter = Menu::create(menuItemStart,menuItemQuit, NULL);

    menuCenter->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5));
    menuCenter->setColor(Color3B(0.0f, 100.f, 0.0f));
    menuCenter->alignItemsVerticallyWithPadding(30);

    addChild(menuCenter);

    return true;
}

void GameMenu::startGame(Ref* psender)
{
    auto scence = GameScene::createGameScene();
    Director::getInstance()->replaceScene(scence);
}

void GameMenu::quit(Ref* psender)
{
    Director::getInstance()->end();
}