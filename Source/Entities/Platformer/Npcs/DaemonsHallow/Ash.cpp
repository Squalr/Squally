#include "Ash.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ash::MapKey = "ash";

Ash* Ash::deserialize(ValueMap& properties)
{
	Ash* instance = new Ash(properties);

	instance->autorelease();

	return instance;
}

Ash::Ash(ValueMap& properties) : super(properties,
	Ash::MapKey,
	EntityResources::Npcs_DaemonsHallow_Ash_Animations,
	EntityResources::Npcs_DaemonsHallow_Ash_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Ash::~Ash()
{
}

Vec2 Ash::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ash::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Ash::create();
}
