#include "Leroy.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Leroy::MapKey = "leroy";

Leroy* Leroy::deserialize(ValueMap& properties)
{
	Leroy* instance = new Leroy(properties);

	instance->autorelease();

	return instance;
}

Leroy::Leroy(ValueMap& properties) : super(properties,
	Leroy::MapKey,
	EntityResources::Npcs_CastleValgrind_Leroy_Animations,
	EntityResources::Npcs_CastleValgrind_Leroy_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Leroy::~Leroy()
{
}

Vec2 Leroy::getDialogueOffset()
{
	return Vec2(-32.0f, -96.0f);
}

LocalizedString* Leroy::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Leroy::create();
}
