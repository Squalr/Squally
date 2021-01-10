#pragma once

#include "Engine/Animations/Spriter/SpriterAnimationPart.h"

namespace cocos2d
{
	class Sprite;
};

class SpriterAnimationSprite : public SpriterAnimationPart
{
public:
	static SpriterAnimationSprite* create(std::string spriteResource, cocos2d::Vec2 anchor);
	
    void setScaleX(float scaleX) override;
    void setScaleY(float scaleX) override;
    void setAnchorPoint(const cocos2d::Vec2& anchorPoint) override;

protected:
	SpriterAnimationSprite(std::string spriteResource, cocos2d::Vec2 anchor);
	virtual ~SpriterAnimationSprite();

private:
	typedef SpriterAnimationPart super;

	cocos2d::Sprite* sprite;
};
