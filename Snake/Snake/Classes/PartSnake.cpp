#include "PartSnake.h"

PartSnake* PartSnake::createPartSnake(std::string nameSprite)
{
    PartSnake *self = NULL;
    self = new PartSnake();
    self->initWithFile(nameSprite);
    return self;
}