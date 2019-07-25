#pragma once

#include "Engine/SmartNode.h"

// define the constants that are going to define the water surface behaviour
static const int kColumnCount = 160;
static const float kTension = 0.025f;
static const float kDampening = 0.0f;
static const float kSpread = 0.25f;
static cocos2d::Color4B topColor = cocos2d::Color4B(119, 167, 178, 212);
static cocos2d::Color4B bottomColor = cocos2d::Color4B(91, 126, 135, 64);

// define a struct for Vertex we are going to use to draw primitives

namespace cocos2d
{
    class CustomCommand;
}

class LiquidColumn;

class LiquidTop : public SmartNode
{
private:
    typedef SmartNode super;
    friend class LiquidNode;

    struct Vertex
    {
        uint16_t x;
        uint16_t y;

        Vertex() : x(0), y(0) { }
        Vertex(uint16_t x, uint16_t y) : x(x), y(y) { }
    };

    static LiquidTop* create(cocos2d::Size surfaceSize);

    LiquidTop(cocos2d::Size surfaceSize);
    ~LiquidTop();
    
    void onEnter() override;
    void update(float dt) override;
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

    void splash(float index, float speed);
    void onCustomDraw(const cocos2d::Mat4 &transform);

    std::vector<LiquidColumn*> columns;
    Vertex vertexArray[kColumnCount * 2];
    cocos2d::Color4B colorArray[kColumnCount * 2];
    cocos2d::CustomCommand* customCommand;

    cocos2d::Size surfaceSize;
};
