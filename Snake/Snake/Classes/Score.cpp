#include "Score.h"


Score::Score()
{
    auto screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    const int fontSize = 40;
    std::string scoreText = "Score: " + std::to_string(score);
    label = Label::createWithTTF(scoreText,"fonts/arial.ttf", fontSize);
    label->setColor(Color3B::WHITE);

    label->setPosition(Vec2(origin.x + screenSize.width * 0.8, origin.y + screenSize.height * 0.95));

    addChild(label);
    addListeners();
};

Score::~Score()
{
    getEventDispatcher()->removeCustomEventListeners(collisionWithApple);
}

void Score::updateLabel()
{
    label->setString("Score: " + std::to_string(score));
}

void Score::addListeners()
{
    auto hitBrickListener = EventListenerCustom::create(collisionWithApple, [=](EventCustom *event) {
        score += 10;
        updateLabel();
    });
    getEventDispatcher()->addEventListenerWithFixedPriority(hitBrickListener, 1);
}