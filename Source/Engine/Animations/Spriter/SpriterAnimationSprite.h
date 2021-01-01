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
	
    void setAnchorPoint(const cocos2d::Vec2& anchorPoint) override;
    void setHeirarchyScale(const cocos2d::Vec2& scale) override;
	void setDebugDrawHeirarchyDepth();
	void setDebugDrawBoneScale();

protected:
	SpriterAnimationSprite(std::string spriteResource, cocos2d::Vec2 anchor);
	virtual ~SpriterAnimationSprite();

private:
	typedef SpriterAnimationPart super;

	cocos2d::Sprite* sprite;
};
