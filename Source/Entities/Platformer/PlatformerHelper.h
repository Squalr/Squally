#pragma once

#include "Entities/Platformer/PlatformerFriendly.h"

class ClickableNode;

// Base class for player + npcs
class PlatformerHelper : public PlatformerFriendly
{
public:
	static const std::string PlatformerHelperTag;

protected:
	PlatformerHelper(cocos2d::ValueMap& properties,
		std::string entityName,
		std::string scmlResource,
		std::string emblemResource,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		float hoverHeight = 0.0f);
	~PlatformerHelper();

private:
	typedef PlatformerFriendly super;
};
