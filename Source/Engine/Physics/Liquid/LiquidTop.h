#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
    class CustomCommand;
}

class ColumnData;

class LiquidTop : public SmartNode
{
public:
    
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

    struct ColumnData
    {
        float targetHeight = 0.0f;
        float height = 0.0f;
        float speed = 0.0f;

        ColumnData(float targetHeight, float height, float speed) : targetHeight(targetHeight), height(height), speed(speed) { }
    };

    static LiquidTop* create(cocos2d::CSize surfaceSize, cocos2d::Color4B surfaceColor, cocos2d::Color4B bodyColor, float tension, float dampening, float spread);

    LiquidTop(cocos2d::CSize surfaceSize, cocos2d::Color4B surfaceColor, cocos2d::Color4B bodyColor, float tension, float dampening, float spread);
    virtual ~LiquidTop();
    
    void onEnter() override;
    void update(float dt) override;
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

    void splash(float index, float speed, float splashRadius, float decay);
    void onCustomDraw(const cocos2d::Mat4 &transform);

    std::vector<ColumnData> columns;
    std::vector<int> columnIndicies;
    std::vector<Vertex> vertexArray;
    std::vector<float> leftDeltas;
    std::vector<float> rightDeltas;
    std::vector<cocos2d::Color4B> colorArray;
    cocos2d::CustomCommand* customDrawCommand = nullptr;

    cocos2d::CSize surfaceSize;
    float tension = 0.0f;
    float dampening = 0.0f;
    float spread = 0.0f;
    int columnCount = 0;
    int lastIndex = 0;

    static const int ColumnsPer128px;
};
