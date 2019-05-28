#pragma once

#include "Entities/Platformer/PlatformerEntity.h"

class ClickableNode;

// Base class for player + npcs
class PlatformerFriendly : public PlatformerEntity
{
public:

protected:
	PlatformerFriendly(cocos2d::ValueMap& properties,
		std::string scmlResource,
		std::string emblemResource,
		PlatformerCollisionType collisionType,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		int baseHealth,
		int baseSpecial,
		cocos2d::Size movementCollisionSize = cocos2d::Size::ZERO);
	virtual ~PlatformerFriendly();

private:
	typedef PlatformerEntity super;
};
