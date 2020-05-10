#include "Athena.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Athena::MapKey = "athena";

Athena* Athena::deserialize(ValueMap& properties)
{
	Athena* instance = new Athena(properties);

	instance->autorelease();

	return instance;
}

Athena::Athena(ValueMap& properties) : super(properties,
	Athena::MapKey,
	EntityResources::Npcs_UnderflowRuins_Athena_Animations,
	EntityResources::Npcs_UnderflowRuins_Athena_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Athena::~Athena()
{
}

Vec2 Athena::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Athena::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Athena::create();
}
