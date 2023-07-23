#include "Scaldor.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Scaldor::MapKey = "scaldor";

Scaldor* Scaldor::deserialize(ValueMap& properties)
{
	Scaldor* instance = new Scaldor(properties);

	instance->autorelease();

	return instance;
}

Scaldor::Scaldor(ValueMap& properties) : super(properties,
	Scaldor::MapKey,
	EntityResources::Npcs_FirewallFissure_Scaldor_Animations,
	EntityResources::Npcs_FirewallFissure_Scaldor_Emblem,
	CSize(112.0f, 160.0f),
	1.05f)
{
}

Scaldor::~Scaldor()
{
}

Vec2 Scaldor::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Scaldor::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_FirewallFissure_Scaldor::create();
}
