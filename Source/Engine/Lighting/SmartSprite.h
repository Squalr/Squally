#pragma once

#include "cocos/2d/CCSprite.h"

class LightEffect;

class SmartSprite : public cocos2d::Sprite
{
public:
    static SmartSprite* create(const std::string &filename);
    static SmartSprite* createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);
    
    void setEffect(LightEffect* effect, const std::string &normalMapFilename);
    
protected:
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    
    ~SmartSprite();
    
    LightEffect* _effect = nullptr;
    cocos2d::Texture2D* _normalmap = nullptr;
};
