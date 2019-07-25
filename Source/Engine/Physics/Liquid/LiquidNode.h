#pragma once

#include "cocos/renderer/CCCustomCommand.h"

#include "Engine/SmartNode.h"

// define the constants that are going to define the water surface behaviour
static const int kColumnCount = 160;
static const float kTension = 0.025f;
static const float kDampening = 0.0f;
static const float kSpread = 0.25f;
static cocos2d::Color4B topColor = cocos2d::Color4B(119, 167, 178, 255);
static cocos2d::Color4B bottomColor = cocos2d::Color4B(91, 126, 135, 127);

// define a struct for Vertex we are going to use to draw primitives
struct Vertex
{
    uint16_t x;
    uint16_t y;
};

// define a struct for Color we are going to use to draw primitives
struct Color
{
    cocos2d::Color4B color;
};

// forward declarations
class LiquidColumn;

class LiquidNode : public SmartNode
{
public:
    static LiquidNode* create(cocos2d::Size liquidSize);

    void splash(float index, float speed);
    
    // variables
    std::vector<LiquidColumn*> columns;      // a vector of LiquidColumn (nodes, with no autorelease) that represent slices of the water surface
    float scale;                            // the scale, used to determine the width of the surface and the force of the splash
    Vertex vertexArray[kColumnCount * 2];   // the array of Vertex
    Color colorArray[kColumnCount * 2];     // the array of Colors
    cocos2d::CustomCommand customCommand;   // we need a CustomCommand to properly set the zOrder of the Node

protected:
    LiquidNode(cocos2d::Size liquidSize);
    ~LiquidNode();
                 
    void onEnter() override;
    void update(float dt) override;
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

private:
    typedef SmartNode super;

    void onCustomDraw(const cocos2d::Mat4 &transform);

    cocos2d::Size liquidSize;
};
