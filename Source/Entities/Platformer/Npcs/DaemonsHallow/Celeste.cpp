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
	EntityResources::Npcs_DaemonsHallow_Celeste_Animations,
	EntityResources::Npcs_DaemonsHallow_Celeste_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
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
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Celeste::create();
}
