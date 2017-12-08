#include "PartSnake.h"

PartSnake* PartSnake::createPartSnake(std::string nameSprite)
{
    PartSnake *self = nullptr;
    self = new PartSnake();
    self->initWithFile(nameSprite);
    self->autorelease();
    return self;
}