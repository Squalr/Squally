#include "Rusty.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Rusty::MapKey = "rusty";

Rusty* Rusty::deserialize(ValueMap& properties)
{
	Rusty* instance = new Rusty(properties);

	instance->autorelease();

	return instance;
}

Rusty::Rusty(ValueMap& properties) : super(properties,
	Rusty::MapKey,
	EntityResources::Npcs_DataMines_Rusty_Animations,
	EntityResources::Npcs_DataMines_Rusty_Emblem,
	CSize(112.0f, 160.0f),
	1.0f)
{
}

Rusty::~Rusty()
{
}

Vec2 Rusty::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Rusty::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_FirewallFissure_Rusty::create();
}
