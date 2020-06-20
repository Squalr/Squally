#include "Magnus.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Magnus::MapKey = "magnus";

Magnus* Magnus::deserialize(ValueMap& properties)
{
	Magnus* instance = new Magnus(properties);

	instance->autorelease();

	return instance;
}

Magnus::Magnus(ValueMap& properties) : super(properties,
	Magnus::MapKey,
	EntityResources::Npcs_DaemonsHallow_Magnus_Animations,
	EntityResources::Npcs_DaemonsHallow_Magnus_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

Magnus::~Magnus()
{
}

Vec2 Magnus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Magnus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Magnus::create();
}
