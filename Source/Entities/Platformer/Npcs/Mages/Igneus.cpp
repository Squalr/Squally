#include "Igneus.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Igneus::MapKey = "igneus";

Igneus* Igneus::deserialize(ValueMap& properties)
{
	Igneus* instance = new Igneus(properties);

	instance->autorelease();

	return instance;
}

Igneus::Igneus(ValueMap& properties) : super(properties,
	Igneus::MapKey,
	EntityResources::Npcs_Mages_Igneus_Animations,
	EntityResources::Npcs_Mages_Igneus_Emblem,
	CSize(112.0f, 160.0f),
	1.05f)
{
}

Igneus::~Igneus()
{
}

Vec2 Igneus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Igneus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_FirewallFissure_Igneus::create();
}
