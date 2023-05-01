#include "Cindra.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Cindra::MapKey = "cindra";

Cindra* Cindra::deserialize(ValueMap& properties)
{
	Cindra* instance = new Cindra(properties);

	instance->autorelease();

	return instance;
}

Cindra::Cindra(ValueMap& properties) : super(properties,
	Cindra::MapKey,
	EntityResources::Npcs_FirewallFissure_Cindra_Animations,
	EntityResources::Npcs_FirewallFissure_Cindra_Emblem,
	CSize(112.0f, 160.0f),
	0.85f)
{
}

Cindra::~Cindra()
{
}

Vec2 Cindra::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Cindra::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_FirewallFissure_Cindra::create();
}
