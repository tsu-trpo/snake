#include "PartSnake.h"

PartSnake* PartSnake::createPartSnake(const std::string &nameSprite)
{
    PartSnake *self = new PartSnake;
    self->initWithFile(nameSprite);
    self->autorelease();
    return self;
}

void PartSnake::setImage(const std::string &name)
{
    initWithFile(name);
}

Vec2 PartSnake::getDirectionVec2()
{
    switch(moveDirection) {
        case Direction::up:
            return {0, 1};
        case Direction::down:
            return {0, -1};
        case Direction::left:
            return {-1, 0};
        case Direction::right:
            return {1, 0};
        default:
            throw std::logic_error{"Unexpected case"};
    }
}