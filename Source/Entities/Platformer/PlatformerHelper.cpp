#include "PlatformerHelper.h"

using namespace cocos2d;

const std::string PlatformerHelper::PlatformerHelperTag = "platformer-helper";

PlatformerHelper::PlatformerHelper(
	ValueMap& properties,
	std::string entityName,
	std::string scmlResource,
	std::string emblemResource,
	CSize size, 
	float scale,
	float hoverHeight
	)
	: super(
		properties,
		entityName,
		scmlResource,
		emblemResource,
		size,
		scale,
		hoverHeight
	)
{
	// Tag all friendly entities by class to optimize object queries (ObjectEvents.h)
	this->addTag(PlatformerHelper::PlatformerHelperTag);
}

PlatformerHelper::~PlatformerHelper()
{
}
