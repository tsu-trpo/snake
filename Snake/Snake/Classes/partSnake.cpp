#include "partSnake.h"

partSnake* partSnake::create(std::string name)
{
    partSnake *self = NULL;
    self = new partSnake();
    self->initWithFile(name);
    return self;
}
