#pragma once
#include "Effect.h"
#include "Resources.h"

using namespace cocos2d;

class LightEffect : public Effect
{
public:
	static LightEffect* create();

	void setLightPos(const cocos2d::Vec3& pos);
	void setLightColor(const cocos2d::Color3B& color);
	void setAmbientLightColor(const cocos2d::Color3B& color);
	void setBrightness(float value);
	void setLightCutoffRadius(float value);
	void setLightHalfRadius(float value);

	void prepareForRender(cocos2d::Sprite *sprite, cocos2d::Texture2D *normalmap);

	cocos2d::Color3B getLightColor() const { return _lightColor; }
	cocos2d::Color3B getAmbientLightColor() const { return _ambientLightColor; }

protected:
	bool init();

	cocos2d::Vec3 _lightPos;
	cocos2d::Color3B _lightColor;
	cocos2d::Color3B _ambientLightColor;
	float _lightCutoffRadius;
	float _lightHalfRadius;
	float _brightness;
};
