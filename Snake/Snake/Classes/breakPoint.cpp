#include "breakPoint.h"

void breakPoint::setVar(partSnake* part)
{
    xMovement = part->xMovement;
    yMovement = part->yMovement;
    //breakPointVec2 = part->getPosition();
    posX = part->getPositionX() - 45;
    posY = part->getPositionY();
}

