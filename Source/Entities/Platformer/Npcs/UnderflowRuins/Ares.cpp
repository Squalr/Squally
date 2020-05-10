#include "Ares.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ares::MapKey = "ares";

Ares* Ares::deserialize(ValueMap& properties)
{
	Ares* instance = new Ares(properties);

	instance->autorelease();

	return instance;
}

Ares::Ares(ValueMap& properties) : super(properties,
	Ares::MapKey,
	EntityResources::Npcs_UnderflowRuins_Ares_Animations,
	EntityResources::Npcs_UnderflowRuins_Ares_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Ares::~Ares()
{
}

Vec2 Ares::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ares::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Ares::create();
}
