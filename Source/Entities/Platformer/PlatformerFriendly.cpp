#include "PlatformerFriendly.h"

using namespace cocos2d;

PlatformerFriendly::PlatformerFriendly(
	cocos2d::ValueMap& initProperties,
	std::string scmlResource,
	std::string emblemResource,
	PlatformerCollisionType collisionType, 
	cocos2d::Size size, 
	float scale,
	cocos2d::Vec2 collisionOffset,
	int baseHealth,
	int baseSpecial)
	: super(initProperties, scmlResource, emblemResource, collisionType, size, scale, collisionOffset, baseHealth, baseSpecial)
{
}

PlatformerFriendly::~PlatformerFriendly()
{
}
