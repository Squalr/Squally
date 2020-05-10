#include "Merlin.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Merlin::MapKey = "merlin";

Merlin* Merlin::deserialize(ValueMap& properties)
{
	Merlin* instance = new Merlin(properties);

	instance->autorelease();

	return instance;
}

Merlin::Merlin(ValueMap& properties) : super(properties,
	Merlin::MapKey,
	EntityResources::Npcs_CastleValgrind_Merlin_Animations,
	EntityResources::Npcs_CastleValgrind_Merlin_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Merlin::~Merlin()
{
}

Vec2 Merlin::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Merlin::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Merlin::create();
}
