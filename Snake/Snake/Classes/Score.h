#pragma once
#include "cocos2d.h"
#include "GlobalConstants.h"

using namespace cocos2d;

class Score : public Node
{
    unsigned int score = 0;
    Label *label = nullptr;

    void updateLabel();
    void addListeners();
public:
    Score();
    ~Score();
};