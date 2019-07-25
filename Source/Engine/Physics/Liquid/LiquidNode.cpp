#include "LiquidNode.h"

#include "cocos/2d/CCLayer.h"

#include "Engine/Physics/Liquid/LiquidTop.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

LiquidNode* LiquidNode::create(Size liquidSize, float surfaceDepth)
{
    LiquidNode* instance = new LiquidNode(liquidSize, surfaceDepth);

    instance->autorelease();

    return instance;
}

LiquidNode::LiquidNode(Size liquidSize, float surfaceDepth)
{
    this->liquidSize = liquidSize;
    this->surfaceDepth = MathUtils::clamp(surfaceDepth, 0.0f, liquidSize.height);
    this->liquidSize.height = MathUtils::clamp(this->liquidSize.height, this->surfaceDepth, liquidSize.height);
    this->liquidBody = LayerColor::create(bottomColor, this->liquidSize.width, this->liquidSize.height - this->surfaceDepth);
    this->liquidTop = LiquidTop::create(Size(this->liquidSize.width, this->surfaceDepth));

    this->addChild(this->liquidBody);
    this->addChild(this->liquidTop);
}

LiquidNode::~LiquidNode()
{
}

void LiquidNode::initializePositions()
{
    super::initializePositions();

    const float HackySeamFix = 10.0f;

    this->liquidTop->setPosition(Vec2(-this->liquidSize.width / 2.0f, this->liquidSize.height / 2.0f - this->surfaceDepth));
    this->liquidBody->setPosition(Vec2(-this->liquidSize.width / 2.0f, -this->liquidSize.height / 2.0f));
}

void LiquidNode::splash(float x, float speed)
{
    this->liquidTop->splash(x, speed);
}
