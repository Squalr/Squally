#include "Hades.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hades::MapKey = "hades";

Hades* Hades::deserialize(ValueMap& properties)
{
	Hades* instance = new Hades(properties);

	instance->autorelease();

	return instance;
}

Hades::Hades(ValueMap& properties) : super(properties,
	Hades::MapKey,
	EntityResources::Npcs_UnderflowRuins_Hades_Animations,
	EntityResources::Npcs_UnderflowRuins_Hades_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Hades::~Hades()
{
}

Vec2 Hades::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Hades::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Hades::create();
}
