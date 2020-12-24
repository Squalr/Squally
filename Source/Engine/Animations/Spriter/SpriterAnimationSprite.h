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
	/*
    void setScaleX(float scaleX) override;
    void setScaleY(float scaleY) override;
	*/
    void visit(cocos2d::Renderer* renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

	void setDebugDrawHeirarchyDepth();
	void setDebugDrawBoneScale();

protected:
	SpriterAnimationSprite(std::string spriteResource, cocos2d::Vec2 anchor);
	virtual ~SpriterAnimationSprite();

private:
	typedef SmartNode super;

	cocos2d::Sprite* sprite;
};
