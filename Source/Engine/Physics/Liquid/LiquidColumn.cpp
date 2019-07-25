#include "LiquidColumn.h"

using namespace cocos2d;

bool LiquidColumn::init()
{
    // super init
    Node::init();
    
    return true;
}

void LiquidColumn::initWithTargetHeight(float targetHeight, float height, float speed)
{
    this->targetHeight = targetHeight;
    this->height = height;
    this->speed = speed;
}

void LiquidColumn::update(float dampening, float tension)
{
    float deltaHeight = targetHeight - height;
    speed += tension * deltaHeight - speed * dampening;
    height += speed;
}
