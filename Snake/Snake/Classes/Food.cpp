#include "Food.h"
#include "sizeGameScene.h"
#include "Snake.h"

Food* Food::create()
{
    Food *self = NULL;
    self = new Food();
    self->initWithFile("apple.png");

    return self;
}

void Food::spawn()
{
     float startPoint = 0;
     Size screenSize = Director::getInstance()->getVisibleSize();
     this->setPosition(random(startPoint,screenSize.width), random(startPoint,screenSize.height));
}
