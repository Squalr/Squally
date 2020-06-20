#include "Aphrodite.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Aphrodite::MapKey = "aphrodite";

Aphrodite* Aphrodite::deserialize(ValueMap& properties)
{
	Aphrodite* instance = new Aphrodite(properties);

	instance->autorelease();

	return instance;
}

Aphrodite::Aphrodite(ValueMap& properties) : super(properties,
	Aphrodite::MapKey,
	EntityResources::Npcs_UnderflowRuins_Aphrodite_Animations,
	EntityResources::Npcs_UnderflowRuins_Aphrodite_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Aphrodite::~Aphrodite()
{
}

Vec2 Aphrodite::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Aphrodite::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Aphrodite::create();
}
