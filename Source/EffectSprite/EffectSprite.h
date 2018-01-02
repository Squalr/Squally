#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class LightEffect;

class EffectSprite : public cocos2d::Sprite
{
public:
	static EffectSprite *create(const std::string &filename);
	static EffectSprite *createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);

	void setEffect(LightEffect *newEffect, const std::string &normalMapFilename);

protected:
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

	~EffectSprite();

	LightEffect * effect = nullptr;
	cocos2d::Texture2D * normalmap = nullptr;
};
