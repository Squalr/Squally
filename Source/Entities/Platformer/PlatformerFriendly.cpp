#include "PlatformerFriendly.h"

using namespace cocos2d;

PlatformerFriendly::PlatformerFriendly(
	ValueMap& properties,
	std::string scmlResource,
	std::string emblemResource,
	PlatformerCollisionType collisionType, 
	Size size, 
	float scale,
	Vec2 collisionOffset,
	int baseHealth,
	int baseSpecial,
	float hoverHeight,
	std::string inventorySaveKey,
	std::string equipmentSaveKey,
	std::string currencySaveKey
	)
	: super(
		properties,
		scmlResource,
		emblemResource,
		collisionType,
		size,
		scale,
		collisionOffset,
		baseHealth,
		baseSpecial,
		hoverHeight,
		inventorySaveKey,
		equipmentSaveKey,
		currencySaveKey
	)
{
}

PlatformerFriendly::~PlatformerFriendly()
{
}
