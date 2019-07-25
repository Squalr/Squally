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
    static LiquidNode* create(cocos2d::Size liquidSize, float surfaceDepth = 64.0f);

    void splash(float index, float speed);

protected:
    LiquidNode(cocos2d::Size liquidSize, float surfaceDepth);
    ~LiquidNode();
    
    void initializePositions() override;

private:
    typedef SmartNode super;

    cocos2d::Size liquidSize;
    float surfaceDepth;

    cocos2d::LayerColor* liquidBody;
    LiquidTop* liquidTop;
};
