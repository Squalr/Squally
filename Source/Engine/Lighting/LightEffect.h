#pragma once

#include "Engine/Lighting/Effect.h"

namespace cocos2d
{
    class Sprite;
    class Texture2D;
}

class LightEffect : public Effect
{
public:
    static LightEffect* create(std::string fragmentShader);
    
    void setLightPos(const cocos2d::Vec3& pos);
    void setLightColor(const cocos2d::Color3B& color);
    void setAmbientLightColor(const cocos2d::Color3B& color);
    void setBrightness(float value);
    void setLightCutoffRadius(float value);
    void setLightHalfRadius(float value);
    
    void prepareForRender(cocos2d::Sprite *sprite, cocos2d::Texture2D* normalmap);
    
    cocos2d::Color3B getLightColor() const { return _lightColor; }
    cocos2d::Color3B getAmbientLightColor() const { return _ambientLightColor; }

protected:
    LightEffect(std::string fragmentShader);
    virtual ~LightEffect();

private:
    bool init();

    cocos2d::Vec3 _lightPos;
    cocos2d::Color3B _lightColor;
    cocos2d::Color3B _ambientLightColor;
    float _lightCutoffRadius;
    float _lightHalfRadius;
    float _brightness;
};
