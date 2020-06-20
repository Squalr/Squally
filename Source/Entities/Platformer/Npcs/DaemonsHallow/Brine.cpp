#include "Brine.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Brine::MapKey = "brine";

Brine* Brine::deserialize(ValueMap& properties)
{
	Brine* instance = new Brine(properties);

	instance->autorelease();

	return instance;
}

Brine::Brine(ValueMap& properties) : super(properties,
	Brine::MapKey,
	EntityResources::Npcs_DaemonsHallow_Brine_Animations,
	EntityResources::Npcs_DaemonsHallow_Brine_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Brine::~Brine()
{
}

Vec2 Brine::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Brine::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Brine::create();
}
