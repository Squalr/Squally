#include "Reindeer.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Reindeer::MapKey = "Reindeer";

Reindeer* Reindeer::deserialize(ValueMap& properties)
{
	Reindeer* instance = new Reindeer(properties);

	instance->autorelease();

	return instance;
}

Reindeer::Reindeer(ValueMap& properties) : super(properties,
	Reindeer::MapKey,
	EntityResources::Misc_BallmerPeaks_Reindeer_Animations,
	EntityResources::Misc_BallmerPeaks_Reindeer_Emblem,
	CSize(192.0f, 160.0f),
	1.0f)
{
}

Reindeer::~Reindeer()
{
}

Vec2 Reindeer::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Reindeer::getEntityName()
{
	return Strings::Platformer_Entities_Names_Critters_Reindeer::create();
}
