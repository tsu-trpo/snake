#include "Food.h"

Food* Food::createApple()
{
    Food *self = new Food();
    self->initWithFile(appleImage);
    self->autorelease();

    return self;
}

void Food::setRandomPositionApple()
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size screenSize = Director::getInstance()->getVisibleSize();
    setPosition(random(origin.x,screenSize.width), random(origin.y,screenSize.height));
}