#include "PartSnake.h"

PartSnake* PartSnake::createPartSnake(const std::string &nameSprite)
{
    PartSnake *self = new PartSnake;
    self->initWithFile(nameSprite);
    self->autorelease();
    return self;
}