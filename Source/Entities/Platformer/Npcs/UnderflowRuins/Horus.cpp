#include "Horus.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Horus::MapKey = "horus";

Horus* Horus::deserialize(ValueMap& properties)
{
	Horus* instance = new Horus(properties);

	instance->autorelease();

	return instance;
}

Horus::Horus(ValueMap& properties) : super(properties,
	Horus::MapKey,
	EntityResources::Npcs_UnderflowRuins_Horus_Animations,
	EntityResources::Npcs_UnderflowRuins_Horus_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Horus::~Horus()
{
}

Vec2 Horus::getDialogueOffset()
{
	return Vec2(-32.0f, -128.0f);
}

LocalizedString* Horus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Horus::create();
}
