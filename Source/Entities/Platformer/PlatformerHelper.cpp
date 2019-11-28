#include "PlatformerHelper.h"

using namespace cocos2d;

const std::string PlatformerHelper::PlatformerHelperTag = "platformer-helper";

PlatformerHelper::PlatformerHelper(
	ValueMap& properties,
	std::string entityName,
	std::string scmlResource,
	std::string emblemResource,
	Size size, 
	float scale,
	Vec2 collisionOffset,
	float hoverHeight
	)
	: super(
		properties,
		entityName,
		scmlResource,
		emblemResource,
		size,
		scale,
		collisionOffset,
		hoverHeight
	)
{
	// Tag all friendly entities by class to optimize object queries (ObjectEvents.h)
	this->addTag(PlatformerHelper::PlatformerHelperTag);
}

PlatformerHelper::~PlatformerHelper()
{
}
