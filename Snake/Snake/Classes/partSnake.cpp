#include "partSnake.h"

partSnake* partSnake::create(std::string name)
{
    partSnake *self = NULL;
    self = new partSnake();
    self->initWithFile(name);
    return self;
}
 void partSnake::rotate( std::string name)
 {
     this->initWithFile(name);
 }