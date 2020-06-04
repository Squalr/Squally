#include "YetiBaby.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string YetiBaby::MapKey = "yeti-baby";

YetiBaby* YetiBaby::deserialize(ValueMap& properties)
{
	YetiBaby* instance = new YetiBaby(properties);

	instance->autorelease();

	return instance;
}

YetiBaby::YetiBaby(ValueMap& properties) : super(properties,
	YetiBaby::MapKey,
	EntityResources::Helpers_BallmerPeaks_YetiBaby_Animations,
	EntityResources::Helpers_BallmerPeaks_YetiBaby_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
}

YetiBaby::~YetiBaby()
{
}

Vec2 YetiBaby::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* YetiBaby::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_BallmerPeaks_YetiBaby::create();
}
