#include "Luna.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Luna::MapKey = "luna";

Luna* Luna::deserialize(ValueMap& properties)
{
	Luna* instance = new Luna(properties);

	instance->autorelease();

	return instance;
}

Luna::Luna(ValueMap& properties) : super(properties,
	Luna::MapKey,
	EntityResources::Npcs_BallmerPeaks_Luna_Animations,
	EntityResources::Npcs_BallmerPeaks_Luna_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Luna::~Luna()
{
}

Vec2 Luna::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Luna::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BallmerPeaks_Luna::create();
}
