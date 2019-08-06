#pragma once
#include "cocos/2d/CCSprite.h"
#include "cocos/math/Vec2.h"

#include "Entities/Platformer/PlatformerFriendly.h"

class ClickableNode;

class NpcBase : public PlatformerFriendly
{
public:

protected:
	NpcBase(cocos2d::ValueMap& properties,
		std::string scmlResource,
		std::string emblemResource,
		PlatformerCollisionType collisionType,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		int baseHealth,
		int baseSpecial);
	virtual ~NpcBase();

	void update(float) override;

protected:
	virtual void onInteractButtonClick();

private:
	typedef PlatformerFriendly super;
	friend class NpcCollisionBehaviors;

	cocos2d::Sprite* chatBubbleSprite;
	ClickableNode* interactButton;
};
