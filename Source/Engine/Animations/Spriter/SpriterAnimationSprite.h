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
	void setSpriteResource(const std::string& spriteResource) override;
	void restoreSpriteResource() override;
	std::string getSpriteResource() const override;
	cocos2d::CSize getSpriteSize() const override;

protected:
	SpriterAnimationSprite(std::string spriteResource, cocos2d::Vec2 anchor);
	virtual ~SpriterAnimationSprite();

	void applyAnchorPoint(const cocos2d::Vec2& anchorPoint) override;
	void applyAnimationOffset(const cocos2d::Vec2& offset) override;

private:
	typedef SpriterAnimationPart super;
	bool usesCompatibilityLayout() const;
	void refreshSpriteLayout();

	cocos2d::Sprite* sprite = nullptr;
	std::string originalSpriteResource;
	std::string currentSpriteResource;
	cocos2d::Vec2 currentAnchor = cocos2d::Vec2::ZERO;
};
