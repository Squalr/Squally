#include "Hera.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hera::MapKey = "hera";

Hera* Hera::deserialize(ValueMap& properties)
{
	Hera* instance = new Hera(properties);

	instance->autorelease();

	return instance;
}

Hera::Hera(ValueMap& properties) : super(properties,
	Hera::MapKey,
	EntityResources::Npcs_UnderflowRuins_Hera_Animations,
	EntityResources::Npcs_UnderflowRuins_Hera_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Hera::~Hera()
{
}

Vec2 Hera::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Hera::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Hera::create();
}
