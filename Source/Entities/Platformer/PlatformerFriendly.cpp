#include "PlatformerFriendly.h"

using namespace cocos2d;

const std::string PlatformerFriendly::PlatformerFriendlyTag = "platformer-friendly";

PlatformerFriendly::PlatformerFriendly(
	ValueMap& properties,
	std::string entityName,
	std::string scmlResource,
	std::string emblemResource,
	Size size, 
	float scale,
	Vec2 collisionOffset,
	float hoverHeight,
	std::string inventorySaveKey,
	std::string equipmentSaveKey,
	std::string currencySaveKey
	)
	: super(
		properties,
		entityName,
		scmlResource,
		emblemResource,
		size,
		scale,
		collisionOffset,
		hoverHeight,
		inventorySaveKey,
		equipmentSaveKey,
		currencySaveKey
	)
{
	// Tag all friendly entities by class to optimize object queries (ObjectEvents.h)
	this->addTag(PlatformerFriendly::PlatformerFriendlyTag);
}

PlatformerFriendly::~PlatformerFriendly()
{
}
