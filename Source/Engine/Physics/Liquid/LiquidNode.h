#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
    class LayerColor;
}

class LiquidTop;

class LiquidNode : public SmartNode
{
public:
    static LiquidNode* create(cocos2d::Size liquidSize, float surfaceDepth, cocos2d::Color4B surfaceColor, cocos2d::Color4B bodyColor);

    void splash(float x, float speed, float splashRadius = 64.0f, float decay = 0.05f);

protected:
    LiquidNode(cocos2d::Size liquidSize, float surfaceDepth, cocos2d::Color4B surfaceColor, cocos2d::Color4B bodyColor);
    virtual ~LiquidNode();
    
    void initializePositions() override;

private:
    typedef SmartNode super;

    cocos2d::Size liquidSize;
    float surfaceDepth;

    cocos2d::LayerColor* liquidBody;
    LiquidTop* liquidTop;
};
