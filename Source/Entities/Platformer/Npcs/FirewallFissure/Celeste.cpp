#include "Celeste.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Celeste::MapKey = "celeste";

Celeste* Celeste::deserialize(ValueMap& properties)
{
	Celeste* instance = new Celeste(properties);

	instance->autorelease();

	return instance;
}

Celeste::Celeste(ValueMap& properties) : super(properties,
	Celeste::MapKey,
	EntityResources::Npcs_FirewallFissure_Celeste_Animations,
	EntityResources::Npcs_FirewallFissure_Celeste_Emblem,
	CSize(112.0f, 160.0f),
	0.85f)
{
}

Celeste::~Celeste()
{
}

Vec2 Celeste::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Celeste::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_FirewallFissure_Celeste::create();
}
