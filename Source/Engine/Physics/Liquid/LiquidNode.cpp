#include "LiquidNode.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCLayer.h"

#include "Engine/Physics/Liquid/LiquidTop.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

LiquidNode* LiquidNode::create(Size liquidSize, float surfaceDepth, Color4B surfaceColor, Color4B bodyColor)
{
    LiquidNode* instance = new LiquidNode(liquidSize, surfaceDepth, surfaceColor, bodyColor);

    instance->autorelease();

    return instance;
}

LiquidNode::LiquidNode(Size liquidSize, float surfaceDepth, Color4B surfaceColor, Color4B bodyColor)
{
    const float kTension = 0.015f;
    const float kDampening = 0.005f;
    const float kSpread = 0.05f;

    this->liquidSize = liquidSize;
    this->surfaceDepth = MathUtils::clamp(surfaceDepth, 0.0f, liquidSize.height);
    this->liquidSize.height = MathUtils::clamp(this->liquidSize.height, this->surfaceDepth, liquidSize.height);
    this->liquidBody = LayerColor::create(bodyColor, this->liquidSize.width, this->liquidSize.height - this->surfaceDepth);
    this->liquidTop = LiquidTop::create(Size(this->liquidSize.width, this->surfaceDepth), surfaceColor, bodyColor, kTension, kDampening, kSpread);
    this->edges = DrawNode::create();

    this->edges->drawSegment(Vec2(-liquidSize.width / 2.0f, liquidSize.height / 2.0f), Vec2(-liquidSize.width / 2.0f, -liquidSize.height / 2.0f), 2.0f, Color4F(surfaceColor));
    this->edges->drawSegment(Vec2(-liquidSize.width / 2.0f, -liquidSize.height / 2.0f), Vec2(liquidSize.width / 2.0f, -liquidSize.height / 2.0f), 2.0f, Color4F(surfaceColor));
    this->edges->drawSegment(Vec2(liquidSize.width / 2.0f, -liquidSize.height / 2.0f), Vec2(liquidSize.width / 2.0f, liquidSize.height / 2.0f), 2.0f, Color4F(surfaceColor));

    this->addChild(this->liquidBody);
    this->addChild(this->liquidTop);
    this->addChild(this->edges);
}

LiquidNode::~LiquidNode()
{
}

void LiquidNode::initializePositions()
{
    super::initializePositions();

    this->liquidTop->setPosition(Vec2(-this->liquidSize.width / 2.0f, this->liquidSize.height / 2.0f - this->surfaceDepth));
    this->liquidBody->setPosition(Vec2(-this->liquidSize.width / 2.0f, -this->liquidSize.height / 2.0f));
}

void LiquidNode::splash(float x, float speed, float splashRadius, float decay)
{
    this->liquidTop->splash(x, speed, splashRadius, decay);
}
