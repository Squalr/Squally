#include "Leon.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Leon::MapKey = "leon";

Leon* Leon::deserialize(ValueMap& properties)
{
	Leon* instance = new Leon(properties);

	instance->autorelease();

	return instance;
}

Leon::Leon(ValueMap& properties) : super(properties,
	Leon::MapKey,
	EntityResources::Npcs_VoidStar_Leon_Animations,
	EntityResources::Npcs_VoidStar_Leon_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Leon::~Leon()
{
}

Vec2 Leon::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Leon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Leon::create();
}
