#pragma once
#include "cocos/2d/CCSprite.h"
#include "cocos/base/ccTypes.h"
#include "cocos/math/Vec2.h"

#include "Entities/Platformer/PlatformerEntity.h"

class MenuSprite;

class NpcBase : public PlatformerEntity
{
protected:
	NpcBase(cocos2d::ValueMap* initProperties,
		std::string scmlResource,
		PlatformerCollisionType collisionType,
		cocos2d::Size size = cocos2d::Size(256.0f, 256.0f),
		float scale = 1.0f,
		cocos2d::Vec2 collisionOffset = cocos2d::Vec2(0.0f, 0.0f));
	~NpcBase();

	void update(float) override;

protected:
	virtual void initializeCollisionEvents() override;
	virtual void onInteractButtonClick(MenuSprite* menuSprite);

private:
	typedef PlatformerEntity super;
	cocos2d::Sprite* chatBubbleSprite;
	MenuSprite* interactButton;
};
