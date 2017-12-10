#include "Food.h"

Food* Food::createApple()
{
    Food *self = new Food();
    self->initWithFile(appleImage);
    self->autorelease();

    return self;
}

void Food::spawnApple()
{
    float startPoint = 0;
    Size screenSize = Director::getInstance()->getVisibleSize();
    this->setPosition(random(startPoint,screenSize.width), random(startPoint,screenSize.height));
}